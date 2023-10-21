#ifndef _COMPHPP
#define _COMPHPP

#include <iostream>
#include "biblioteca/tads/List.hpp"
#include "biblioteca/tads/huffman/HuffmanSetup.hpp"
#include "biblioteca/tads/huffman/Progress.hpp"
#include "biblioteca/funciones/strings.hpp"
using namespace std;

void contarOcurrencias(string fName, HuffmanTable tabla[])
{
}

void crearLista(List<HuffmanTreeInfo> &lista, HuffmanTable tabla[])
{
}

HuffmanTreeInfo *crearArbol(List<HuffmanTreeInfo> &lista)
{
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