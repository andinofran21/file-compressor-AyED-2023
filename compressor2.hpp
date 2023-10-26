#ifndef _COMPHPP
#define _COMPHPP

#include <iostream>
#include <string.h>
#include "biblioteca/funciones/files.hpp"
#include "biblioteca/tads/List.hpp"
#include "biblioteca/tads/huffman/HuffmanSetup.hpp"
// #include "biblioteca/tads/huffman/Progress.hpp"
#include "biblioteca/funciones/strings.hpp"
using namespace std;

struct Hoja
{
    char c;
    char length;
    string code;
};

struct Cabecera
{
    char cantHojas;
    List<Hoja> lH;
    unsigned int longArchi;
};

Hoja hoja(char c, char lenght, string code)
{
    return {c, lenght, code};
}

Cabecera cabecera(char cantHojas, List<Hoja> lst, unsigned int longArchi)
{
    return {cantHojas, lst, longArchi};
}

int _cmpOcurrencias(HuffmanTreeInfo *c1, HuffmanTreeInfo *c2)
{
    // si la cantidad de ocurrencias es igual, ordeno alfabeticamente por codigo ASCII
    return c1->n == c2->n ? c1->c - c2->c : c1->n - c2->n;
}

void contarOcurrencias(string fName, HuffmanTable tabla[])
{
    // tabla[256] = {0, ""};
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

char contarHojas(HuffmanTable tabla[])
{
    int cont=0;
    for (int i = 0; i < 256; i++) // cuento la cantidad de hojas del arbol
    {
        if (tabla[i].n != 0)
        {
            cont++;
        }
    }
    char ret = (char)cont;

    return ret;
}

List<Hoja> crearListaHojas(HuffmanTable tabla[])
{
    List<Hoja> lH = list<Hoja>();
    for (int i = 0; i < 256; i++)
    {
        if (tabla[i].n != 0)
        {
            int l = length(tabla[i].cod);
            int mult = (l / 8);
            string m = tabla[i].cod;
            Hoja h = hoja(intToChar(i), intToChar(l), rpad(tabla[i].cod, 8 + 8 * mult, 0));
            //rpad rellena con 0 a la derecha hasta obtener un largo de codigo que sea multiplo de 8
            listAdd<Hoja>(lH, h);
        }
    }
}

//escribimos la cabecera que generamos en el archivo .huf
void cargarCabecera(FILE *fHuf, Cabecera cab)
{
}

void comprimirArchivo(FILE *f, FILE *fHuf, HuffmanTable tabla[])
{
}

void grabarArchivoComprimido(string fName, HuffmanTable tabla[])
{
    // cantidad de hojas del arbol
    char t = contarHojas(tabla);

    FILE *f = fopen(fName.c_str(), "r+b");

    // longitud del archivo
    unsigned int longArch = fileSize<unsigned char>(f);

    // Lista de hojas con los respectivos codigos
    List<Hoja> lH = crearListaHojas(tabla);

    // generar la cabecera del archivo
    Cabecera cab = cabecera(t, lH, longArch);

    // creamos el archivo .huf
    string archivoHuf = fName + ".huf";
    FILE *fHuf = fopen(archivoHuf.c_str(), "w+b");

    // escribimos la cabecera en el archivo .huf
    cargarCabecera(fHuf, cab);

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