#ifndef _COMPHPP
#define _COMPHPP

#include <iostream>
#include <string.h>
#include "biblioteca/tads/List.hpp"
#include "biblioteca/funciones/files.hpp"
#include "biblioteca/funciones/strings.hpp"
#include "biblioteca/tads/BitWriter2.hpp"
#include "biblioteca/tads/huffman/HuffmanSetup.hpp"
#include "Progress.hpp"
using namespace std;


int _cmpOcurrencias(HuffmanTreeInfo *c1, HuffmanTreeInfo *c2)
{
    // si la cantidad de ocurrencias es igual, ordeno alfabeticamente por codigo ASCII
    return c1->n == c2->n ? c1->c - c2->c : c1->n - c2->n;
}

//Crea la tabla de ocurrencias, y guarda la cantidada de ocurrencias para cada caracter
void contarOcurrencias(string fName, HuffmanTable tabla[])
{
    // inicializamos la tabla
    for (int i = 0; i < 256; i++)
    {
        tabla[i].n = 0;
        tabla[i].cod = "";
    }
    FILE *f = fopen(fName.c_str(), "r+b");

    // armamos la tabla con los caracteres y la cantidad de ocurrencias
    unsigned char c = read<unsigned char>(f);
    while (!feof(f))
    {
        tabla[c].n++;
        c = read<unsigned char>(f);
    }

    fclose(f);
}

// Recorro la tabla y añado a la lista los caracteres que aparecieron
void crearLista(List<HuffmanTreeInfo *> &lista, HuffmanTable tabla[])
{
    // recorro la tabla y añado a la lista los caracteres que aparecieron
    for (int i = 0; i < 256; i++)
    {
        if (tabla[i].n > 0)
        {
            HuffmanTreeInfo *car = huffmanTreeInfo(i, tabla[i].n, NULL, NULL);
            listAdd<HuffmanTreeInfo *>(lista, car);
        }
    }
    // ordeno la lista
    listSort<HuffmanTreeInfo *>(lista, _cmpOcurrencias);
}

//Recorre la lista mientras crear el arbol
HuffmanTreeInfo *crearArbol(List<HuffmanTreeInfo *> &lista)
{
    // Creamos los elementos h1 y h2 e inicializamos un contador en 0
    HuffmanTreeInfo *h1;
    HuffmanTreeInfo *h2;
    int i = 0;

    // Iteramos mientras haya mas de un elemento en la lista
    while (listSize<HuffmanTreeInfo *>(lista) > 1) // → error en la 3ra iteracion
    {
        // removemos los primeros dos elementos de la lista
        h1 = listRemoveFirst<HuffmanTreeInfo *>(lista);
        h2 = listRemoveFirst<HuffmanTreeInfo *>(lista);

        // creamos un nuevo nodo con la sumatoria de las ocurrencias de h1 y h2
        unsigned int nom = 256 + i;
        HuffmanTreeInfo *nodo = huffmanTreeInfo(nom, h1->n + h2->n, h2, h1);

        // insertamos el nodo en la lista para ir formando el arbol
        listOrderedInsert<HuffmanTreeInfo *>(lista, nodo, _cmpOcurrencias);

        i++;
    }

    return *listNext<HuffmanTreeInfo *>(lista);
}

//Guardamos los codigosHuffman en una tabla
void cargarCodigoEnTabla(HuffmanTreeInfo *raiz, HuffmanTable tabla[])
{
    // creamos el arbol Huffman a partir de la raiz del arbol generado
    HuffmanTree ht = huffmanTree(raiz);
    string aux;
    while (huffmanTreeHasNext(ht))
    {
        // leemos una hoja y cargamos el codigo(camino) en la tabla
        HuffmanTreeInfo *hoja = huffmanTreeNext(ht, aux);
        tabla[hoja->c].cod = aux;
    }
}

// cuento la cantidad de hojas del arbol
char contarHojas(HuffmanTable tabla[])
{
    int cont=0;
    for (int i = 0; i < 256; i++)
    {
        if (tabla[i].n != 0) //si el caracter aparece, incremento el contador
        {
            cont++;
        }
    }
    unsigned char ret = cont-1;

    return ret;
}

//Grabamos en un archivo el caracter,la longitud y su correspondiente cod. Huffman
void grabarHojas(HuffmanTable tabla[], FILE* fHuf)
{
    BitWriter bw = bitWriter(fHuf);
    for (int i = 0; i < 256; i++)
    {
        if (tabla[i].n != 0)
        {
            unsigned char c = i;                     //caracter c
            unsigned char l = length(tabla[i].cod);  //longitud del cod
            string m = tabla[i].cod;        //codigo huffman (no completo con ceros)
            
            write<unsigned char>(fHuf,c);    // grabamos el caracter
            write<unsigned char>(fHuf,l);    // grabamos la longitud
            
            //usamos bitWriterFlush para completar con ceros m y grabar en f
            bitWriterWrite(bw,m);   
            bitWriterFlush(bw);     // grabamos el codigo Huffman de c
        }
    }
}

//escribimos la cabecera que generamos en el archivo .huf
void cargarCabecera(FILE *f, HuffmanTable tabla[],FILE *fHuf)
{
    //escribimos la cantidad de hojas del arbol
    unsigned char cantHojas = contarHojas(tabla);
    write<unsigned char>(fHuf,cantHojas); 

    // escribimos los t registros con la informacion de las hojas
    grabarHojas(tabla,fHuf);

    // longitud del archivo
    unsigned int longArch = fileSize<unsigned char>(f);
    write<unsigned int>(fHuf,longArch); //escribimos la long del archivo original
}

void comprimirArchivo(FILE *f, FILE *fHuf, HuffmanTable tabla[])
{
    BitWriter bw = bitWriter(fHuf);

    // inicilizo el proceso de compresion con el tamaño del archivo a comprimir
    Progress p = progress(fileSize<unsigned char>(f));

    seek<unsigned char>(f,0); //nos posicionamos al principio del archivo original
    while(!feof(f)) //reescribimos el archivo comprimiendo
    {
        unsigned char c = read<unsigned char>(f);
        bitWriterWrite(bw,tabla[c].cod);

        // Actualizar el progreso basado en la cantidad de bytes leídos
        progressShow(p);
    }
    bitWriterFlush(bw); //si quedan elementos dentro de bw los termino de escribir
    progressShowDuration(p);
}

void grabarArchivoComprimido(string fName, HuffmanTable tabla[])
{
    // Abrimos el archivo original
    FILE *f = fopen(fName.c_str(), "r+b");

    // Creamos el archivo .huf
    string fHufName = fName + ".huf";
    FILE *fHuf = fopen(fHufName.c_str(), "w+b");

    // Grabamos la cabecera en el archivo .huf
    cargarCabecera(f,tabla,fHuf);

    /*Recorrer byte por byte. Por cada byte que leemos accedemos a la tabla y copiamos dentro del archivo
    .huf el codigo comprimido correspondiente a ese byte.*/
    comprimirArchivo(f, fHuf, tabla);

    fclose(f);
    fclose(fHuf);
}

void _mostrarArbol(HuffmanTreeInfo *root)
{
    // recorremos el arbol usando TAD HuffmanTree
    HuffmanTree ht = huffmanTree(root);

    string cod;

    // iteramos mientras queden hojas por visitar
    while (huffmanTreeHasNext(ht))
    {
        // obtenemos un puntero a la proxima hoja
        HuffmanTreeInfo *x = huffmanTreeNext(ht, cod);

        // mostramos por pantalla lo que obtubimos
        cout << x->c << ", (" << x->n << "), "
             << "[" << cod << "]" << endl;
    }
}

#endif