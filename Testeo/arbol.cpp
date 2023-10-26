#include <iostream>
#include "../biblioteca/funciones/strings.hpp"
#include "../biblioteca/funciones/files.hpp"
#include "../biblioteca/tads/Array.hpp"
#include "../biblioteca/tads/List_v2.hpp"
#include "../biblioteca/tads/Stack.hpp"
#include "../biblioteca/tads/Queue.hpp"
#include "../biblioteca/tads/BitWriter.hpp"
#include "../biblioteca/tads/BitReader.hpp"
#include "../biblioteca/tads/huffman/HuffmanSetup.hpp"
// #include "../AlgoritmosAFondo_EMPTY_v2.7.18/src/biblioteca/tads/huffman/Progress.hpp"
#include <string.h>
using namespace std;

int cmpOcurrencias(HuffmanTreeInfo *c1, HuffmanTreeInfo *c2)
{
    // si la cantidad de ocurrencias es igual, ordeno alfabeticamente por codigo ASCII
    return c1->n == c2->n ? c1->c - c2->c : c1->n - c2->n;
}

int main()
{
    FILE *f = fopen("texto.txt", "r+b");
    HuffmanTable tabla[256] = {0,""};

    // PASO 1: Contar ocurrencias
    // armamos la tabla con los caracteres y la cantidad de ocurrencias
    unsigned char c = read<unsigned char>(f);
    while (!feof(f))
    {
        tabla[c].n++;
        cout << c;
        c = read<unsigned char>(f);
    }
    cout << endl;

    // ---------------------------------------------------------------------------
    // PASO 2: Crear lista
    List<HuffmanTreeInfo*> arbol = list<HuffmanTreeInfo*>();

    // recorro la tabla y añado a la lista los caracteres que aparecieron
    for (int i = 0; i < 256; i++)
    {
        if (tabla[i].n > 0)
        {
            HuffmanTreeInfo *car = huffmanTreeInfo(i, tabla[i].n, NULL, NULL);
            listAdd<HuffmanTreeInfo*>(arbol, car);
        }
    }

    // ordeno la lista
    listSort<HuffmanTreeInfo*>(arbol, cmpOcurrencias);

    // ---------------------------------------------------------------------------
    // PASO 3: Crear arbol

    // Creamos los elementos h1 y h2 e inicializamos un contador en 0
    HuffmanTreeInfo *h1;
    HuffmanTreeInfo *h2;
    HuffmanTreeInfo *root;
    int i = 0;

    // Iteramos mientras haya mas de un elemento en la lista
    while (listSize<HuffmanTreeInfo*>(arbol) > 1) // → error en la 3ra iteracion
    {
        // removemos los primeros dos elementos de la lista
        h1 = listRemoveFirst<HuffmanTreeInfo*>(arbol);
        h2 = listRemoveFirst<HuffmanTreeInfo*>(arbol);

        // creamos un nuevo nodo con la sumatoria de las ocurrencias de h1 y h2
        long nom = 256 + i;
        HuffmanTreeInfo *nodo = huffmanTreeInfo(nom, h1->n + h2->n, h2, h1);

        // insertamos el nodo en la lista para ir formando el arbol
        listOrderedInsert<HuffmanTreeInfo*>(arbol, nodo, cmpOcurrencias);

        i++;
    }

    root = *listNext<HuffmanTreeInfo*>(arbol);
    /*HuffmanTreeInfo* h3 = huffmanTreeInfo(255+i,h1.n+h2.n,&h2,&h1);
    listAdd<HuffmanTreeInfo>(arbol,*h3);
    listReset<HuffmanTreeInfo>(arbol);
    root = listNext<HuffmanTreeInfo>(arbol);*/

    // ---------------------------------------------------------------------------
    // Cargar codigo en la tabla

    HuffmanTree ht = huffmanTree(root);
    string aux;

    while (huffmanTreeHasNext(ht))
    {
        // obtenemos un puntero a la proxima hoja
        HuffmanTreeInfo *x = huffmanTreeNext(ht, aux);

        // mostramos por pantalla lo que obtubimos
        cout << x->c << ", (" << x->n << "), "
             << "[" << aux << "]" << endl;
    }

    /* while(huffmanTreeHasNext(ht))
    {
        HuffmanTreeInfo* hoja = huffmanTreeNext(ht,aux);
        tabla[hoja->c].cod=aux;
    }

    for(int i=0;i<256;i++) //mostrar tabla con la codificacion
    {
        if(tabla[i].n>0)
        {
            cout << "caracter " << (char)i << tabla[i].n << tabla[i].cod << endl;
        }
    } */

    // ---------------------------------------------------------------------------
    // Grabar archivo comprimido

    // listAdd<HuffmanTreeInfo>(arbol,*h3);

    // muestro la lista
    /* listReset<HuffmanTreeInfo>(arbol);
    while (listHasNext<HuffmanTreeInfo>(arbol))
    {
        HuffmanTreeInfo *c = listNext<HuffmanTreeInfo>(arbol);
        cout << c->c << "  " << c->n << endl;
    } */

    /* for(int i=0;i<256;i++)
    {
        cout<<tabla[c].n<<endl;
    } */

    fclose(f);
    return 0;
}