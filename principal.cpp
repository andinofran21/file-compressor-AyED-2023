#ifndef _MAIN
#define _MAIN

#include <iostream>
#include "biblioteca/funciones/strings.hpp"
#include "compressor2.hpp"
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
    // paso 1
    HuffmanTable tabla[256];
    contarOcurrencias(fName, tabla);

    // paso 2
    List<HuffmanTreeInfo*> lista = list<HuffmanTreeInfo*>();
    crearLista(lista, tabla);

    // paso 3
    HuffmanTreeInfo *raiz = crearArbol(lista);

    // Recorro el arbol para obtener los codigos y los cargo
    // en el array de contenedores, en el campo code
    cargarCodigoEnTabla(raiz, tabla);

    // Grabo el archivo comprimido
    grabarArchivoComprimido(fName, tabla);
}

void descomprimir(string fName)
{
    int filePos;
    // Recomponemos el arbol huffman
    HuffmanTreeInfo *raiz = recomponerArbol(fName, filePos);

    // Grabo el archivo descomprimido
    grabarArchivoDescomprimido(fName,filePos,raiz);

}

#endif