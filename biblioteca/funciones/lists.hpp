#ifndef _TLIST_T_
#define _TLIST_T_

#include <iostream>
#include <stdio.h>

template <typename T>
struct Node
{
   T info;
   Node<T> *sig;
};

// Agrega el elemento e al final de la lista direccionada por p.
// Retorna la dirección del nodo que contiene al elemento que se agregó.
template <typename T>
Node<T> *add(Node<T> *&p, T e)
{
   Node<T> *nuevo = new Node<T>();
   nuevo->info = e;
   nuevo->sig = NULL;

   if (p != NULL)
   {
      Node<T> *aux = p;
      while (aux->sig != NULL)
      {
         aux = aux->sig;
      }
      aux->sig = nuevo;
   }
   else
   {
      p = nuevo;
   }

   return nuevo;
}

// Agrega el elemento e al inicio de la lista direccionada por p.
// Retorna la dirección del nodo que contiene al elemento que se agregó.
template <typename T>
Node<T> *addFirst(Node<T> *&p, T e)
{
   Node<T> *nuevo = new Node<T>();
   nuevo->info = e;
   nuevo->sig = p;
   p = nuevo;

   return nuevo;
}

// Remueve la primera ocurrencia del elemento concordante con cmpTK.
// Retorna el valor del elemento que fue removido.
template <typename T, typename K>
T remove(Node<T> *&p, K k, int cmpTK(T, K))
{
   // si el elemento no existe se produce un error en la linea 102
   T ret;

   /* if (p != NULL && cmpTK(p->info, k) != 0)
   {
      Node<T> *nodoAnt = p;
      Node<T> *aux = nodoAnt->sig;
      while (aux != NULL && cmpTK(aux->info, k) != 0)
      {
         nodoAnt = aux;
         aux = aux->sig;
      }

      ret = aux->info;
      nodoAnt->sig = aux->sig;

      delete aux;
   }
   else
   {
      ret = p->info;
      p = p->sig;
   } */

   Node<T> *aux = p;
   Node<T> *nodoAnt;
   while (aux != NULL && cmpTK(aux->info, k) != 0)
   {
      nodoAnt = aux;
      aux = aux->sig;
   }

   if (p != aux)
   {
      nodoAnt->sig = aux->sig;
   }
   else
   {
      p = aux->sig;
   }

   ret = aux->info;
   delete aux;

   return ret;
}

// Remueve el primer elemento de la lista direccionada por p.
// Retorna el valor del elemento que acabamos de remover.
template <typename T>
T removeFirst(Node<T> *&p)
{
   Node<T> *aux = p;
   T ret = aux->info;
   p = aux->sig;

   delete aux;
   return ret;
}

// Retorna la dirección del nodo que contiene la primera ocurrencia de k, según cmpTK, o
// NULL si ningún elemento concuerda con dicha clave de búsqueda.
template <typename T, typename K>
Node<T> *find(Node<T> *p, K k, int cmpTK(T, K))
{
   Node<T> *ret = p;
   while (ret != NULL && cmpTK(ret->info, k) != 0)
   {
      ret = ret->sig;
   }

   return ret;
}

// Inserta el elemento e en la lista direccionada por p según el criterio que establece la función cmpTT.
// La lista debe estar vacía u ordenada según cmpTT.
// Retorna la dirección del nodo que acabamos de insertar.
template <typename T>
Node<T> *orderedInsert(Node<T> *&p, T e, int cmpTT(T, T))
{
   Node<T> *nuevo = new Node<T>();
   nuevo->info = e;

   Node<T> *aux = p;
   Node<T> *nodoAnt;
   while (aux != NULL && cmpTT(aux->info, e) < 0)
   {
      nodoAnt = aux;
      aux = aux->sig;
   }
   // si es distinto del primero o NULL inserta,
   if (aux != p)
   {
      nodoAnt->sig = nuevo;
   }
   else
   {
      p = nuevo;
   }

   nuevo->sig = aux;

   return nuevo;
}
// Busca en la lista direccionada por p la primera ocurrencia de e, y retorna la dirección del nodo que lo contiene.
// Si e no existe en la lista entonces lo insertar en orden, según el criterio establecido por cmpTT
// La lista debe estar vacía u ordenada según cmpTT
// Retorna la dirección del nodo insertado, y asigna true o false a enc según e fue encontrado o insertado
template <typename T>
Node<T> *searchAndInsert(Node<T> *&p, T e, bool &enc, int cmpTT(T, T))
{
   Node<T> *ret = find<T, T>(p, e, cmpTT);
   enc = true;
   if (ret == NULL)
   {
      ret = orderedInsert<T>(p, e, cmpTT);
      enc = false;
   }
   return ret;
}

// Ordena la lista direccionada por p según el criterio que establece la función de comparación cmpTT.
template <typename T>
void sort(Node<T> *&p, int cmpTT(T, T))
{
   // Implementacion de ordenamiento Bubble sort mejorado
   Node<T> *i;
   Node<T> *j;
   bool ordenado = false;

   while (p != NULL && !ordenado)
   {
      ordenado = true;
      i = p;
      j = p->sig;
      while (j != NULL)
      {
         if (cmpTT(j->info, i->info) < 0)
         {
            ordenado = false;
            T t = i->info;
            i->info = j->info;
            j->info = t;
         }
         i = i->sig;
         j = j->sig;
      }
   }
}

// Indica si la lista direccionada por p tiene o no elemento
// Retorna true o false según la lista tenga o no elementos
template <typename T>
bool isEmpty(Node<T> *p)
{
   return p == NULL ? true : false;
}

// Libera la memoria que utiliza lista direccionada por p. Asigna NULL a p.
template <typename T>
void free(Node<T> *&p)
{
   Node<T> *aux;
   while(p!=NULL)
   {
      aux = p->sig;
      delete p;
      p = aux;
   }
}

// Inserta un nodo conteniendo a e al inicio de la lista direccionada por p.
// Retorna la dirección del nodo que contiene al elemento que se agregó.
template <typename T>
Node<T> *push(Node<T> *&p, T e)
{
   return addFirst<T>(p,e);
}

// Remueve el primer nodo de la lista direccionada por p.
// Retorna el elemento que contenía el nodo que fue removido.
template <typename T>
T pop(Node<T> *&p)
{
   return removeFirst<T>(p);
}

// Agrega el elemento e al final la lista direccionada por q.
// Retorna la dirección del nodo que contiene al elemento que se agregó.
template <typename T>
Node<T> *enqueue(Node<T> *&p, Node<T> *&q, T e)
{
   // agilizo el proceso tomando como referencia el ultimo nodo para añadir el nuevo elemento 
   if(p!=NULL)
   {
      q = add<T>(q,e);
   }
   else
   {
      q = add<T>(p,e);
   } 
   
   return q;
}

// Agrega el elemento e al final la lista circular direccionada por q.
// Retorna la dirección del nodo que contiene al elemento que se agregó.
template <typename T>
Node<T> *enqueue(Node<T> *&q, T e)
{
   Node<T> *nuevo = new Node<T>();
   nuevo->info = e;
   
   if(q!=NULL)
   {
      nuevo->sig = q->sig;
      q->sig = nuevo;  
   }
   else
   {
      nuevo->sig = nuevo;
   }

   q = nuevo;

   return nuevo;
}

// Remueve el primer nodo de la lista direccionada por p.
// Retorna el elemento que contenía el nodo que fue removido.
template <typename T>
T dequeue(Node<T> *&p, Node<T> *&q)
{
   return removeFirst<T>(p);
}

// Remueve el primer nodo de la lista circular direccionada por q.
// Retorna el elemento que contenía el nodo que fue removido
template <typename T>
T dequeue(Node<T> *&q)
{
   T ret;
   Node<T> *aux = q->sig;
   q->sig = aux->sig;
   ret = aux->info;

   if(aux==q)
   {
      q=NULL;
   }

   delete aux;
   return ret;
}

#endif
