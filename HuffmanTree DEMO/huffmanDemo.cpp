#include <iostream>
#include "biblioteca/tads/huffman/HuffmanSetup.hpp"
// #include "biblioteca/tads/huffman/Progress.hpp"
#include <string.h>
using namespace std;

int main()
{
    // crea un arbol huffman demo (para tener algo que recorrer)
    HuffmanTreeInfo *root = huffmanTreeCreateDemoTree();

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

    return 0;
}