#include <iostream>
#include "../biblioteca/funciones/strings.hpp"
#include "../biblioteca/funciones/files.hpp"
#include "../biblioteca/tads/Array.hpp"
#include "../biblioteca/tads/List.hpp"
#include "../biblioteca/tads/Stack.hpp"
#include "../biblioteca/tads/Queue.hpp"
#include "../biblioteca/tads/BitWriter.hpp"
#include "../biblioteca/tads/BitReader.hpp"
#include "../biblioteca/tads/huffman/HuffmanSetup.hpp"
// #include "../AlgoritmosAFondo_EMPTY_v2.7.18/src/biblioteca/tads/huffman/Progress.hpp"
#include <string.h>
using namespace std;

struct Caracter
{
    int c;
    int cont;
};

int cmpOcurrencias(HuffmanTreeInfo c1, HuffmanTreeInfo c2)
{
    // si la cantidad de ocurrencias es igual, ordeno alfabeticamente por codigo ASCII
    return c1.n == c2.n ? c1.c - c2.c : c1.n - c2.n;
}

int main()
{
    FILE *f = fopen("texto.txt", "r+b");
    unsigned int tabla[256] = {0};

    // PASO 1: Contar ocurrencias
    // armamos la tabla con los caracteres y la cantidad de ocurrencias
    unsigned char c = read<unsigned char>(f);
    while (!feof(f))
    {
        tabla[c-1]++;
        cout << c;
        c = read<unsigned char>(f);
    }
    cout << endl;



    // ---------------------------------------------------------------------------
    // PASO 2: Crear lista
    List<HuffmanTreeInfo> arbol = list<HuffmanTreeInfo>();

    // recorro la tabla y añado a la lista los caracteres que aparecieron
    for (unsigned int i = 0; i < 256; i++)
    {
        if (tabla[i] > 0)
        {
            HuffmanTreeInfo *car = huffmanTreeInfo(i,tabla[i],NULL,NULL);
            listAdd<HuffmanTreeInfo>(arbol, *car);
        }
    }

    // ordeno la lista
    listSort<HuffmanTreeInfo>(arbol, cmpOcurrencias);



    // ---------------------------------------------------------------------------
    // PASO 3: Crear arbol

    // Creamos los elementos h1 y h2 e inicializamos un contador en 0
    HuffmanTreeInfo h1;
    HuffmanTreeInfo h2;
    int i = 0;

    // Iteramos mientras haya mas de un elemento en la lista
    while(listHasNext<HuffmanTreeInfo>(arbol))
    {
        // removemos los primeros dos elementos de la lista
        h1 = listRemoveFirst<HuffmanTreeInfo>(arbol);
        h2 = listRemoveFirst<HuffmanTreeInfo>(arbol);

        // creamos un nuevo nodo con la sumatoria de las ocurrencias de h1 y h2
        unsigned int nom = (unsigned int)255+i;
        HuffmanTreeInfo *nodo = huffmanTreeInfo(nom,h1.n+h2.n,&h2,&h1);

        // insertamos el nodo en la lista para ir formando el arbol
        listOrderedInsert<HuffmanTreeInfo>(arbol, *nodo, cmpOcurrencias);

        // aumentamos el contador y confirmamos que haya mas de un elemento en la lista
        i++;
        listReset<HuffmanTreeInfo>(arbol);
        listNext<HuffmanTreeInfo>(arbol);
    }



    // ---------------------------------------------------------------------------
    // Cargar codigo en la tabla 



    // ---------------------------------------------------------------------------
    // Grabar archivo comprimido


    //listAdd<HuffmanTreeInfo>(arbol,*h3);

    // muestro la lista
    listReset<HuffmanTreeInfo>(arbol);
    while(listHasNext<HuffmanTreeInfo>(arbol))
    {
        HuffmanTreeInfo *c = listNext<HuffmanTreeInfo>(arbol);
        cout<<c->c<<"  "<<c->n<<endl;
    }

    /* for(int i=0;i<256;i++)
    {
        cout<<tabla[c].n<<endl;
    } */

    fclose(f);
    return 0;
}