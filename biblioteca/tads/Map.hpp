
#ifndef _TMAP_TAD_
#define _TMAP_TAD_

#include <iostream>
#include "Array.hpp"

using namespace std;

template<typename K,typename V>
struct Map
{
   Array<K> keys;
   Array<V> values;
   int curr;
};

// Inicializa un map.
template<typename K,typename V>
Map<K,V> map()
{
   Map<K,V> m={array<K>(),array<V>(),0};
   return m;
}

// Retorna la dirección de memoria del valor asociado a la clave k o NULL si m no contiene ningún valor asociado a dicha clave.
template<typename K,typename V>
V* mapGet(Map<K,V> m,K k)
{
   V* ret = NULL;
   int size = arraySize<K>(m.keys);
   for(int i=0;i<size;i++)
   {
      if(*arrayGet<K>(m.keys,i)==k)
      {
         ret=arrayGet<V>(m.values,i);
         i=size;
      }
   }

   return ret;
}

// Agrega al map m el elemento v asociado a la clave k. 
// Si existía una entrada vinculada a k se debe reemplazar el valor anterior por v.
// Retorna la dirección de memoria del elemento vinculado con la clave k
template<typename K,typename V>
V* mapPut(Map<K,V>& m,K k,V v)
{
   V* ret = mapGet<K,V>(m,k);
   if(ret==NULL)
   {
      arrayAdd<K>(m.keys,k);
      arrayAdd<V>(m.values,v);
      ret=arrayGet<V>(m.values,m.curr); // direccion que ocupa en el array
      m.curr++;
   }
   else
   {
      *ret=v;
   }
   
   return ret;
}

// Verifica si m contiene a k.
template<typename K,typename V>
bool mapContains(Map<K,V> m,K k)
{
   bool ret=false;

   if(mapGet<K,V>(m,k)!=NULL)
   {
      ret=true;
   }
   
   return ret;
}

// Elimina de m la entrada identificada con la clave k.
// retorna el valor que contenía la entrada asociada a la clave k.
template<typename K,typename V>
V mapRemove(Map<K,V>& m,K k)
{
   V ret;
   int size = arraySize<K>(m.keys);
   for(int i=0;i<size;i++)
   {
      if(*arrayGet<K>(m.keys,i)==k)
      {
         arrayRemove<K>(m.keys,i);
         ret=arrayRemove<V>(m.values,i);
         i=size;
      }
   }

   m.curr--;
   return ret;
}

// Elimina todas las entradas del map m.
template<typename K,typename V>
void mapRemoveAll(Map<K,V>& m)
{
   arrayRemoveAll<K>(m.keys);
   arrayRemoveAll<V>(m.values);
   m.curr=0;
}

// Retorna la cantidad actual de entradas que tiene m.
template<typename K,typename V>
int mapSize(Map<K,V> m)
{
   return arraySize<K>(m.keys);
}

// Indica si quedan más elementos para continuar iterando el map.
template<typename K,typename V>
bool mapHasNext(Map<K,V> m)
{
   return m.curr<arraySize<K>(m.keys)?true:false;
}

// Permite iterar sobre las claves del map. Esta función es mutuamente excluyente respecto de mapNextValue.
// Retorna la siguiente clave dentro de una iteración.
template<typename K,typename V>
K mapNextKey(Map<K,V>& m)
{
   m.curr++;
   return *arrayGet<K>(m.keys,m.curr-1);
}

// Permite iterar sobre los valores que contiene el map. Esta función es mu-tuamente excluyente despecto de mapNextKey.
// Retorna la dirección de memoria del siguiente valor dentro de una iteración.
template<typename K,typename V>
V* mapNextValue(Map<K,V>& m)
{
   m.curr++;
   return arrayGet<V>(m.values,m.curr-1);
}

// prepara el map para comenzar una nueva iteración.
template<typename K,typename V>
void mapReset(Map<K,V>& m)
{
   m.curr=0;
}

// descubre (busca, y si no encuentre agrega) una entrada {k,v} en el map m
template<typename K,typename V>
V* mapDiscover(Map<K,V>& m,K k,V v)
{
   V* ret=mapGet<K,V>(m,k);
   if(ret==NULL)
   {
      ret=mapPut<K,V>(m,k,v);
   }

   return ret;
}

// Ordena el map aplicando sobre sus claves el criterio que establece cmpKK
template<typename K,typename V>
void mapSortByKeys(Map<K,V>& m,int cmpKK(K,K))
{
   // implementacion de ordenamiento por burbujeo, si esta ordenado deja de iterar
   bool ordenado = false;
   int size = arraySize(m.keys);

   while (!ordenado)
   {
      ordenado = true;
      for (int i = 0; i < size-1; i++)
      {
         K k1 = *arrayGet<K>(m.keys,i);
         K k2 = *arrayGet<K>(m.keys,i+1);

         if (cmpKK(k1, k2) > 0)
         {
            ordenado = false;

            V v1 = *arrayGet<V>(m.values,i);
            V v2 = *arrayGet<V>(m.values,i+1);

            arraySet<K>(m.keys,i,k2);
            arraySet<K>(m.keys,i+1,k1);
            arraySet<V>(m.values,i,v2);
            arraySet<V>(m.values,i+1,v1);
         }
      }
   }

}

template<typename K,typename V>
void mapSortByValues(Map<K,V>& m,int cmpVV(V,V))
{
   // implementacion de ordenamiento por burbujeo, si esta ordenado deja de iterar
   bool ordenado = false;
   int size = arraySize(m.keys);

   while (!ordenado)
   {
      ordenado = true;
      for (int i = 0; i < size-1; i++)
      {
         V v1 = *arrayGet<V>(m.values,i);
         V v2 = *arrayGet<V>(m.values,i+1);

         if (cmpVV(v1, v2) > 0)
         {
            ordenado = false;

            K k1 = *arrayGet<K>(m.keys,i);
            K k2 = *arrayGet<K>(m.keys,i+1);

            arraySet<K>(m.keys,i,k2);
            arraySet<K>(m.keys,i+1,k1);
            arraySet<V>(m.values,i,v2);
            arraySet<V>(m.values,i+1,v1);
         }
      }
   }
}

#endif
