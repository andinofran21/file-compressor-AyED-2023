#ifndef _TLIST_TAD_
#define _TLIST_TAD_

#include <iostream>
#include "../funciones/lists.hpp"

using namespace std;

template <typename T>
struct List
{
   Node<T> *head;
   Node<T> *last;
   int size;
};

template <typename T>
void _updateLast(List<T> &lst)
{
   lst.last = lst.head;
   while (lst.last->sig != NULL)
   {
      lst.last = lst.last->sig;
   }
}

// Función de inicialización.
template <typename T>
List<T> list()
{
   return {NULL, NULL, 0};
}

// Agrega un elemento al final de la lista.
// Retorna la dirección de memoria del elemento que se agregó.
template <typename T>
T *listAdd(List<T> &lst, T e)
{
   // Si por error, reseteo la lista, y quiero volver a agregar un elemento,
   // el condicional asegura que dicho elemento se almacenara al final de la lista
   if (lst.last != lst.head) // ANTES: lst.head!=NULL
   {
      lst.last = add<T>(lst.last, e);
   }
   else
   {
      lst.last = add<T>(lst.head, e);
   }

   lst.size++;
   return &lst.last->info;
}

// Agrega el elemento e al inicio de la lista.
// Retorna la dirección de memoria del elemento que se agregó.
template <typename T>
T *listAddFirst(List<T> &lst, T e)
{
   if (lst.head != NULL)
   {
      addFirst<T>(lst.head, e);
   }
   else
   {
      listAdd<T>(lst, e);
   }

   lst.size++;
   return &lst.head->info;
}

// Remueve el elemento que concuerde con k según la función cmpTK.
// Retorna el elemento que fue removido.
template <typename T, typename K>
T listRemove(List<T> &lst, K k, int cmpTK(T, K))
{
   T ret = remove<T>(lst.head, k, cmpTK);
   lst.size--;
   /* if (ret == lst.last->info)
   {
      _updateLast(lst);
   } */
   return ret;
}

// Desenlaza y libera el primer nodo de la lista enlazada
// Retorna el elemento que contenía el (ex) primer nodo de la lista.
template <typename T>
T listRemoveFirst(List<T> &lst)
{
   T ret = removeFirst<T>(lst.head);
   lst.size--;
   if (isEmpty(lst.head))
   {
      lst.last = lst.head;
   }
   return ret;
}

// Retorna la dirección del primer elemento concordante con k según cmpTK o NULL si hubo concordancia.
template <typename T, typename K>
T *listFind(List<T> lst, K k, int cmpTK(T, K))
{
   Node<T> *ret = find<T, K>(lst.head, k, cmpTK);
   return &ret->info;
}

// Indica si la lista está vacía o tiene elementos.
// Retorna true si la lista está vacía, false si tiene elementos.
template <typename T>
bool listIsEmpty(List<T> lst)
{
   return isEmpty<T>(lst.head);
}

// Retorna la cantidad de elementos que tiene la lista.
template <typename T>
int listSize(List<T> lst)
{
   return lst.size;
}

// Libera la memoria que ocupa la lista
template <typename T>
void listFree(List<T> &lst)
{
   free<T>(lst.head);
   free<T>(lst.last);
   lst.size = 0;
}

// Descubre el elemento t en la lista lst.
// Retorna la dirección del elemento encontrado, o recientemente agregado al final de la lista lst.
template <typename T>
T *listDiscover(List<T> &lst, T t, int cmpTT(T, T))
{
   T *ret = listFind<T, T>(lst, t, cmpTT);

   if (ret == NULL)
   {
      ret = listAdd<T>(lst, t);
   }
   return ret;
}

// Inserta un elemento según el orden que establece cmpTT.
// La lista debe estar ordenada (según cmpTT) o vacía.
// Retorna la dirección del elemento insertado.
template <typename T>
T *listOrderedInsert(List<T> &lst, T t, int cmpTT(T, T))
{
   Node<T> *ret = orderedInsert<T>(lst.head, t, cmpTT);
   if (lst.head->sig==NULL || lst.last->sig == ret) // Actualizacion de lst.last OK
   {
      lst.last = ret;
   }
   lst.size++;
   return &ret->info;
}

// Ordena la lista según el criterio que establece cmpTT.
template <typename T>
void listSort(List<T> &lst, int cmpTT(T, T))
{
   sort<T>(lst.head, cmpTT); // No hay problema con lst.last
}

// Prepara la lista para iterarla.
template <typename T>
void listReset(List<T> &lst)
{
   lst.size = 0;
   lst.last = lst.head;
}

// Indica si quedan más elementos para seguir iterando la lista.
// true si es posible seguir iterando la lista.
template <typename T>
bool listHasNext(List<T> lst)
{
   return lst.last != NULL ? true : false;
}

// Retorna la dirección del siguiente elemento de la lista en la iteración.
template <typename T>
T *listNext(List<T> &lst)
{
   T *ret = &lst.last->info;
   lst.last = lst.last->sig;
   return ret;
}

// Retorna la dirección del siguiente elemento de la lista en la iteración.
template <typename T>
T *listNext(List<T> &lst, bool &endOfList)
{
   T *ret = listNext<T>(lst);
   ret != NULL ? endOfList = false : endOfList = true;

   return ret;
}

#endif
