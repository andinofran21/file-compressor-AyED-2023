#ifndef _DECOMPHPP
#define _DECOMPHPP

#include <iostream>
#include "biblioteca/tads/List.hpp"
#include "biblioteca/tads/BitReader.hpp"
#include "biblioteca/funciones/files.hpp"
#include "biblioteca/tads/huffman/HuffmanSetup.hpp"
// #include "biblioteca/tads/huffman/Progress.hpp"
#include "biblioteca/funciones/strings.hpp"
using namespace std;

void recomponerRama(BitReader br, HuffmanTreeInfo *raiz, int longCod, char caracter)
{
    HuffmanTreeInfo *node = raiz;
    // iteramos hasta recomponer la rama correspondiente a esa hoja
    for (int j = 0; j < longCod; j++)
    {

        int bit = bitReaderRead(br);
        // si es un 1 voy a derecha
        if (bit == 1)
        {
            // si no existe el nodo siguiente de la derecha, lo creo
            if (node->right == NULL)
            {
                node->right = huffmanTreeInfo(257, 0, NULL, NULL);
            }
            // avanzo al siguiente nodo de la derecha
            node = node->right;
        }
        // si es un 0 voy a izquierda
        else
        {
            // si no existe el nodo siguiente de la izquierda, lo cre
            if (node->left == NULL)
            {
                node->left = huffmanTreeInfo(257, 0, NULL, NULL);
            }
            // avanzo al siguiente nodo de la derecha
            node = node->left;
        }
    }
    // cuando completa la longitud del Cod, escribimos el caracter
    node->c = caracter;
}

HuffmanTreeInfo *recomponerArbol(string fName, int &posFile)
{
    // Abrimos el archivo original
    FILE *f = fopen(fName.c_str(), "r+b");

    // Inicializamos las estructuras necesarias
    BitReader br = bitReader(f);
    HuffmanTreeInfo *raiz = huffmanTreeInfo(257, 0, NULL, NULL);

    // guardamos la cantidad de hojas que hay en el arbol huffman
    int cantHojas = read<char>(f);

    // iteramos hasta obtener todas las hojas
    for (int i = 0; i < cantHojas; i++)
    {
        // guardamos el caracter de la hoja correspondiente
        char caracter = read<char>(f);
        int longCod = read<char>(f);
        recomponerRama(br, raiz, longCod, caracter);
    }

    posFile = filePos<char>(f); //guardamos la posicion en el archivo despues de los t registros

    fclose(f);
    return raiz;
}

void grabarArchivoDescomprimido(string fName, int posFile, HuffmanTreeInfo *raiz)
{
    // Abrimos el archivo original
    FILE *f = fopen(fName.c_str(), "r+b");
    seek<char>(f,posFile); //nos posicionamos despues de los t registros

    // Creamos el archivo a descomprimir
    string nomArch = substring(fName, 0, indexOf(fName, ".huf"))+"DESC";
    FILE *fDesc = fopen(nomArch.c_str(), "w+b");

    // longitud del archivo original en bytes
    unsigned int longArchi = read<unsigned int>(f);
    
    BitReader br = bitReader(f);
    int cont=0;
    while (!feof(f) && cont<longArchi)
    {
        HuffmanTreeInfo* aux = raiz;
        while (aux->left != NULL && aux->right != NULL)
        {
            int bit = bitReaderRead(br);
            // si es un 1 voy a derecha
            if (bit == 1)
            {
                // avanzo al siguiente nodo de la derecha
                aux = aux->right;
            }
            // si es un 0 voy a izquierda
            else
            {
                // avanzo al siguiente nodo de la derecha
                aux = aux->left;
            }
        }
        char caracter = aux->c; //cuando llegamos a la hoja, leemos el caracter
        write<char>(fDesc,caracter); //escribimos el caracter original en el archivo descomprimido
        cont++;
    }

    fclose(fDesc);
    fclose(f);
}

#endif