#ifndef _TARR_TAD_
#define _TARR_TAD_

#include <iostream>
#include <stdlib.h>
#include "../funciones/arrays.hpp"

#define CAP_ARRAY 10
using namespace std;

template <typename T>
struct Array
{
   T *a;
   int cap;
   int len;
};

// Inicializa un array cuya capacidad inicial será establecida por defecto
// La longitud del array será 0, y se incrementará a medida que se agreguen o inserten nuevos elementos.
template <typename T>
Array<T> array()
{
   T *a = new T[CAP_ARRAY];
   return {a, CAP_ARRAY, 0};
}

//*** redimensiona el array con el doble de la capacidad que tenia
template <typename T>
void _resize(Array<T> &a)
{
   // creo un array con una nueva capacidad
   T *nuevo = new T[a.cap * 2];

   // copio los datos del array al nuevo
   for (int i = 0; i < a.len; i++)
   {
      nuevo[i] = a.a[i];
   }

   // libero memoria y hago que apunte al nuevo array
   delete a.a;
   a.a = nuevo;
   a.cap *= 2;
}

// Agrega t al final de a incrementando, de ser necesario, su capacidad.
// Retorna la posición del arr donde quedó ubicado el elemento t.
template <typename T>
int arrayAdd(Array<T> &a, T t)
{
   if (a.len == a.cap)
   {
      _resize(a);
   }

   return add<T>(a.a, a.len, t);
}

// Retorna la dirección del elemento de a ubicado en la posición p.
template <typename T>
T *arrayGet(Array<T> a, int p)
{
   return a.a + p; // direccion de memoria que ocupa dentro del array
}

// Asigna el elemento t en la posición p del array a.
template <typename T>
void arraySet(Array<T> &a, int p, T t)
{
   a.a[p] = t;
}

// Inserta t en la posición p del array a.
template <typename T>
void arrayInsert(Array<T> &a, T t, int p)
{
   if (a.len == a.cap)
   {
      _resize(a);
   }
   insert<T>(a.a, a.len, t, p);
}

// Retorna la longitud actual del array.
template <typename T>
int arraySize(Array<T> a)
{
   return a.len;
}

// Remueve el elemento de a ubicado en la posición p.
// Retorna el elemento que ocupaba la posición p dentro de a.
template <typename T>
T arrayRemove(Array<T> &a, int p)
{
   return remove<T>(a.a, a.len, p);
}

// Remueve todos los elemento de a dejándolo vacío, con longitud 0.
template <typename T>
void arrayRemoveAll(Array<T> &a)
{
   a.len=0;
}

// Retorna la posición de la primera ocurrencia de k dentro de a, según la función de comparación cmpTK,
// o un valor negativo si a no contiene a k.
template <typename T, typename K>
int arrayFind(Array<T> a, K k, int cmpTK(T, K))
{
   return find<T, K>(a.a, a.len, k, cmpTK);
}

// Inserta t en a según el criterio de precedencia que establece cmpTT.
// Retorna la posición donde quedó insertado t dentro de a.
// ***El array debe estar ordenado
template <typename T>
int arrayOrderedInsert(Array<T> &a, T t, int cmpTT(T, T))
{
   if (a.len == a.cap)
   {
      _resize(a);
   }
   return orderedInsert<T>(a.a, a.len, t, cmpTT);
}

// Descubre (busca, y si no encuentra lo agrega) al elemento t en el array a.
// Retorna la dirección del elemento encontrado, o recientemente agregado.
template <typename T>
T *arrayDiscover(Array<T> &a, T t, int cmpTT(T, T))
{
   int pos = find<T>(a.a,a.len,t,cmpTT);
   if(pos<0)
   {
      pos=arrayAdd<T>(a,t);
   }

   return arrayGet<T>(a,pos);
}

// Ordena el array a según establece cmpTT.
template <typename T>
void arraySort(Array<T> &a, int cmpTT(T, T))
{
   sort<T>(a.a, a.len, cmpTT);
}

#endif
