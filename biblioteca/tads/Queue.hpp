#ifndef _TQUEUE_TAD_
#define _TQUEUE_TAD_

#include <iostream>
#include "../funciones/lists.hpp"

using namespace std;

template<typename T>
struct Queue
{
   Node<T> *first;
   int size;
};

// Crea una cola vacía.
template<typename T>
Queue<T> queue()
{
   return {NULL,0};
}

// Encola el elemento e
// Retorna la dirección de memoria del elemento que se encoló.
template<typename T>
T* queueEnqueue(Queue<T>& q,T e)
{
   Node<T> *ret = enqueue<T>(q.first,e);
   return &ret->info;
}

// Desencola un elemento.
// Retorna el elemento que se desencoló.
template<typename T>
T queueDequeue(Queue<T>& q)
{
   return dequeue<T>(q.first);
}

// Retorna true o false según la cola tenga elementos o no.
template<typename T>
bool queueIsEmpty(Queue<T> q)
{
   return q.first==NULL?true:false;
}

// Retorna la cantidad de elementos que tiene la cola.
template<typename T>
int queueSize(Queue<T> q)
{
   return q.size;
}

#endif
