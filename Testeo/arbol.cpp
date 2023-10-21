#include <iostream>
#include "../AlgoritmosAFondo_EMPTY_v2.7.18/src/biblioteca/funciones/strings.hpp"
#include "../AlgoritmosAFondo_EMPTY_v2.7.18/src/biblioteca/funciones/files.hpp"
#include "../AlgoritmosAFondo_EMPTY_v2.7.18/src/biblioteca/tads/Array.hpp"
#include "../AlgoritmosAFondo_EMPTY_v2.7.18/src/biblioteca/tads/Map.hpp"
#include "../AlgoritmosAFondo_EMPTY_v2.7.18/src/biblioteca/tads/List.hpp"
#include "../AlgoritmosAFondo_EMPTY_v2.7.18/src/biblioteca/tads/Stack.hpp"
#include "../AlgoritmosAFondo_EMPTY_v2.7.18/src/biblioteca/tads/Queue.hpp"
#include "../AlgoritmosAFondo_EMPTY_v2.7.18/src/biblioteca/tads/BitWriter.hpp"
#include "../AlgoritmosAFondo_EMPTY_v2.7.18/src/biblioteca/tads/BitReader.hpp"
#include "../AlgoritmosAFondo_EMPTY_v2.7.18/src/biblioteca/tads/huffman/HuffmanSetup.hpp"
// #include "../AlgoritmosAFondo_EMPTY_v2.7.18/src/biblioteca/tads/huffman/Progress.hpp"
#include "../AlgoritmosAFondo_EMPTY_v2.7.18/src/principal.hpp"
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
int cmpOcurrencias2(HuffmanTreeInfo c1, HuffmanTreeInfo c2)
{
    // si la cantidad de ocurrencias es igual, ordeno alfabeticamente por codigo ASCII
    return  c1.n - c2.n;
}

int main()
{
    FILE *f = fopen("texto.txt", "r+b");
    unsigned int tabla[256] = {0};

    // PASO 1
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
    // PASO 2
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
    // PASO 3

    // removemos el primer nodo
    HuffmanTreeInfo h1;
    HuffmanTreeInfo h2;
    int i = 0;
    // si hay siguiente

    while(listHasNext<HuffmanTreeInfo>(arbol))
    {
        h1 = listRemoveFirst<HuffmanTreeInfo>(arbol);
        h2 = listRemoveFirst<HuffmanTreeInfo>(arbol);

        unsigned int nom = (unsigned int)255+i;
        HuffmanTreeInfo *nodo = huffmanTreeInfo(nom,h1.n+h2.n,&h2,&h1);

        listOrderedInsert<HuffmanTreeInfo>(arbol, *nodo, cmpOcurrencias);

        i++;
        listReset<HuffmanTreeInfo>(arbol);
        listNext<HuffmanTreeInfo>(arbol);
    }



    // ---------------------------------------------------------------------------
    






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