#ifndef _TSTACK_TAD_
#define _TSTACK_TAD_

#include <iostream>
#include "../funciones/lists.hpp"

using namespace std;

template <typename T>
struct Stack
{
   Node<T> *top;
   int size;
};

// Crea una pila vacía.
template <typename T>
Stack<T> stack()
{
   return {NULL, 0};
}

// Apila el elemento e.
// Retorna la dirección de memoria del elemento que se apiló.
template <typename T>
T *stackPush(Stack<T> &st, T e)
{
   Node<T> *ret = push<T>(st.top, e);
   st.size++;
   return &ret->info;
}

// Desapila un elemento.
// Retorna el elemento que se desapilo
template <typename T>
T stackPop(Stack<T> &st)
{
   st.size--;
   return pop<T>(st.top);
}

// Retorna true o false según la pila tenga elementos o no.
template <typename T>
bool stackIsEmpty(Stack<T> st)
{
   return st.top == NULL ? true : false;
}

// Retorna la cantidad de elementos que tiene la pila.
template <typename T>
int stackSize(Stack<T> st)
{
   return st.size;
}

#endif
