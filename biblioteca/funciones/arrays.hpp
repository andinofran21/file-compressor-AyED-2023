#ifndef _TARRAYS_T_
#define _TARRAYS_T_

#include <iostream>

// Agrega el elemento e al final de arr incrementando su longitud len.
// Retorna a posición del array donde quedó ubicado el elemento e que acabamos de agregar.
template <typename T>
int add(T arr[], int &len, T e)
{
   arr[len] = e;
   len++;
   return len - 1;
}

// Inserta el elemento e en la posición p del array arr.
// Desplaza los elementos ubicados a partir de p+1 e incrementa la longitud len.
template <typename T>
void insert(T arr[], int &len, T e, int p)
{
   for (int i = len; i > p; i--)
   {
      arr[i] = arr[i - 1];
   }

   arr[p] = e;
   len++;
}

// Remueve el elemento ubicado en la posición p del array arr.
// Desplaza ubicados a partir de p y decrementa la longitud len.
// Retorna el elemento que fue removido del array
template <typename T>
T remove(T arr[], int &len, int p)
{
   T ret = arr[p];

   for (int i = p; i < len; i++)
   {
      arr[i] = arr[i + 1];
   }

   len--;
   return ret;
}

// Retorna la posición de la primera ocurrencia de k dentro de arr o un valor negativo si arr no contiene a k.
template <typename T, typename K>
int find(T arr[], int len, K k, int cmpTK(T, K))
{
   //int ret = -1;
   /* for (int i = 0; i < len; i++)
   {
      if (cmpTK(arr[i], k) == 0)
      {
         ret = i;
         i = len;
      }
   } */
   int i = 0;
   while (i < len && cmpTK(arr[i], k) != 0)
   {
      i++;
   }
   // return ret;
   return i < len ? i : -1;
}

// Inserta e dentro de arr según el criterio de precedencia que establece cmpTT.
// Retorna la posición donde dicho elemento quedó insertado
// ***El array debe estar ordenado
template <typename T>
int orderedInsert(T arr[], int &len, T e, int cmpTT(T, T))
{
   int i=0;
   while(i<len && cmpTT(e,arr[i])>0)
   {
      i++;
   }
   insert(arr,len,e,i);
   return i;
}

// Ordena arr según el criterio de precedencia que establece cmpTT.
template <typename T>
void sort(T arr[], int len, int cmpTT(T, T))
{
   // implementacion de ordenamiento por burbujeo, si esta ordenado deja de iterar
   bool ordenado = false;

   while (!ordenado)
   {
      ordenado = true;
      for (int i = 0; i < len-1; i++)
      {
         if (cmpTT(arr[i], arr[i + 1]) > 0)
         {
            ordenado = false;
            T aux = arr[i];
            arr[i] = arr[i + 1];
            arr[i + 1] = aux;
         }
      }
   }
}

#endif
