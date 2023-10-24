#ifndef _COMPHPP
#define _COMPHPP

#include <iostream>
#include <string.h>
#include "biblioteca/funciones/files.hpp"
#include "biblioteca/tads/List.hpp"
#include "biblioteca/tads/huffman/HuffmanSetup.hpp"
#include "biblioteca/tads/huffman/Progress.hpp"
#include "biblioteca/funciones/strings.hpp"
using namespace std;

int _cmpOcurrencias(HuffmanTreeInfo c1, HuffmanTreeInfo c2)
{
    // si la cantidad de ocurrencias es igual, ordeno alfabeticamente por codigo ASCII
    return c1.n == c2.n ? c1.c - c2.c : c1.n - c2.n;
}

void contarOcurrencias(string fName, HuffmanTable tabla[])
{
    tabla[256] = {0, ""};
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

void crearLista(List<HuffmanTreeInfo> &lista, HuffmanTable tabla[])
{
    // recorro la tabla y añado a la lista los caracteres que aparecieron
    for (int i = 0; i < 256; i++)
    {
        if (tabla[i].n > 0)
        {
            HuffmanTreeInfo *car = huffmanTreeInfo(i, tabla[i].n, NULL, NULL);
            listAdd<HuffmanTreeInfo>(lista, *car);
        }
    }
    // ordeno la lista
    listSort<HuffmanTreeInfo>(lista, _cmpOcurrencias);
}

HuffmanTreeInfo *crearArbol(List<HuffmanTreeInfo> &lista)
{
    // Creamos los elementos h1 y h2 e inicializamos un contador en 0
    HuffmanTreeInfo h1;
    HuffmanTreeInfo h2;
    int i = 0;

    // Iteramos mientras haya mas de un elemento en la lista
    while (listSize<HuffmanTreeInfo>(lista) > 1) // → error en la 3ra iteracion
    {
        // removemos los primeros dos elementos de la lista
        h1 = listRemoveFirst<HuffmanTreeInfo>(lista);
        h2 = listRemoveFirst<HuffmanTreeInfo>(lista);

        // creamos un nuevo nodo con la sumatoria de las ocurrencias de h1 y h2
        long nom = 256 + i;
        HuffmanTreeInfo *nodo = huffmanTreeInfo(nom, h1.n + h2.n, &h2, &h1);

        // insertamos el nodo en la lista para ir formando el arbol
        listOrderedInsert<HuffmanTreeInfo>(lista, *nodo, _cmpOcurrencias);

        i++;
    }

    return listNext<HuffmanTreeInfo>(lista);
}

void cargarCodigoEnTabla(HuffmanTreeInfo *raiz, HuffmanTable tabla[]) 
{
}

void grabarArchivoComprimido(string fName, HuffmanTable tabla[])
{
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