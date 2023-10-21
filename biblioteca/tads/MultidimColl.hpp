#ifndef _TMTX_T_
#define _TMTX_T_

#include <iostream>
#include "Coll.hpp"

using namespace std;

template <typename T>
struct Mtx
{
   Coll<T> coll;
   int rows;
};

template <typename T>
Mtx<T> mtx(int f, int c, T valorDefault, string tToString(T))
{
   Mtx<T> m;
   Coll<T> coleccion = coll<T>();

   for (int i = 0; i < f; i++)
   {
      for (int j = 0; j < c; j++)
      {
         collAdd<T>(coleccion, valorDefault, tToString);
      }
   }
   m.coll = coleccion;
   m.rows = f;

   return m;
}

template <typename T>
T mtxGetAt(Mtx<T> m, int f, int c, T tFromString(string))
{
   T t = collGetAt<T>(m.coll, (f * m.rows) + c, tFromString);
   return t;
}

template <typename T>
void mtxSetAt(Mtx<T> &m, T t, int f, int c, string tToString(T))
{
   collSetAt<T>(m.coll, t, (f * m.rows) + c, tToString);
}

// ------------------------

template <typename T>
struct Cube
{
   Coll<T> coll;
   int rows;
   int columns;
};

template <typename T>
Cube<T> cube(int f, int c, int p, T valorDefault, string tToString(T))
{
   Coll<T> coleccion=coll<T>();
   for (int i = 0; i < p; i++)
   {
      for (int j = 0; j < f; j++)
      {
         for (int k = 0; k < c; k++)
         {
            collAdd<T>(coleccion, valorDefault, tToString);
         }
      }
   }

   return {coleccion, f, c};
}

template <typename T>
T cubeGetAt(Cube<T> cu, int f, int c, int p, T tFromString(string))
{
   T t = collGetAt<T>(cu.coll, ((f * cu.rows) + c) + (cu.rows * cu.columns) * p, tFromString);
   return t;
}

template <typename T>
void cubeSetAt(Cube<T> &cu, T t, int f, int c, int p, string tToString(T))
{
   collSetAt<T>(cu.coll, t, ((f * cu.rows) + c) + (cu.rows * cu.columns) * p, tToString);
}

#endif
