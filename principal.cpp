#ifndef _MAIN
#define _MAIN

#include <iostream>
#include "biblioteca/funciones/strings.hpp"
#include "compressor.hpp"
#include "decompressor.hpp"
using namespace std;

void comprimir(string fName);
void descomprimir(string fName);

// int arg, char **argv

int main()
{
    // string fName = argv[1];
    string fName = "zoom.bmp";

    if (!endsWith(fName, ".huf"))
    {
        comprimir(fName);
    }
    else
    {
        descomprimir(fName);
    }

    return 0;
}

void comprimir(string fName)
{
    // Paso 1: Contar ocurrencias
    cout<<"Contando ocurrencias..."<<endl;
    HuffmanTable tabla[256];
    contarOcurrencias(fName, tabla);

    // Paso 2: Crear lista
    cout<<"Creando lista..."<<endl;
    List<HuffmanTreeInfo*> lista = list<HuffmanTreeInfo*>();
    crearLista(lista, tabla);

    // Paso 3: Crear árbol
    cout<<"Creando arbol..."<<endl;
    HuffmanTreeInfo *raiz = crearArbol(lista);

    // Recorro el arbol para obtener los codigos y los cargo
    // en el array de contenedores, en el campo code
    // Paso 4: Cargar códigos en la tabla
    cout<<"Cargando codigos..."<<endl;
    cargarCodigoEnTabla(raiz, tabla);

    // Paso 5: Grabar archivo comprimido
    cout<<"Grabando archivo comprimido..."<<endl;
    grabarArchivoComprimido(fName, tabla);
}

void descomprimir(string fName)
{
    int filePos;
    // Recomponemos el arbol huffman
    cout<<"Recomponiendo arbol Huffman..."<<endl;
    HuffmanTreeInfo *raiz = recomponerArbol(fName, filePos);

    // Grabo el archivo descomprimido
    cout<<"Grabando archivo descomprimido..."<<endl;
    grabarArchivoDescomprimido(fName,filePos,raiz);

}

#endif