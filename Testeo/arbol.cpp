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
#include "../compressor.hpp"
#include "../decompressor.hpp"

// #include "../AlgoritmosAFondo_EMPTY_v2.7.18/src/biblioteca/tads/huffman/Progress.hpp"
#include <string.h>
using namespace std;


int main()
{
    // PASO 1: Contar ocurrencias
    // armamos la tabla con los caracteres y la cantidad de ocurrencias
    HuffmanTable tabla[256];
    string archivo = "texto.txt";
    contarOcurrencias(archivo,tabla);

    // ---------------------------------------------------------------------------
    // PASO 2: Crear lista
    List<HuffmanTreeInfo> lista = list<HuffmanTreeInfo>();
    crearLista(lista,tabla);
  
    // ---------------------------------------------------------------------------
    // PASO 3: Crear arbol
    HuffmanTreeInfo *tree = crearArbol(lista);
  
    // Recorro el arbol para obtener los codigos y los cargo
    // en el array de contenedores, en el campo code
    cargarCodigoEnTabla(tree, tabla);
    
    return 0;
}