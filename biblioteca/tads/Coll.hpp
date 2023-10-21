#ifndef _TCOLL_T_
#define _TCOLL_T_

#include <iostream>
#include "../funciones/strings.hpp"
#include "../funciones/tokens.hpp"

using namespace std;

template<typename T>
struct Coll
{
   string s;
   char sep;
   int point;
};

// inicializacion de la coleccion con sep
template<typename T>
Coll<T> coll(char sep) 
{
   Coll<T> c;
   c.sep=sep;
   c.point=0;
   return c;
}

// inicializacion de la coleccion '|'
template<typename T>
Coll<T> coll() 
{
   Coll<T> c;
   c.sep='|';
   c.point=0;
   return c;
}

// Retorna la cantidad de elementos que contiene la colección c.
template<typename T>
int collSize(Coll<T> c) 
{
   return tokenCount(c.s,c.sep);
}

// Remueve de la colección c todos sus elementos, dejándola vacía.
template<typename T>
void collRemoveAll(Coll<T>& c) 
{
   c.point=0;
   c.s="";
}

// Remueve de la colección c el elemento ubicado en la posición p.
template<typename T>
void collRemoveAt(Coll<T>& c, int p) 
{
   c.point--;
   removeTokenAt(c.s,c.sep,p);
}

//Agrega el elemento t al final de la colección c (devuelve la posicion)
template<typename T>
int collAdd(Coll<T>& c,T t,string tToString(T)) 
{
   addToken(c.s,c.sep,tToString(t));
   c.point++;
   return tokenCount(c.s,c.sep)-1;
   //return c.point-1;
}

// Reemplaza por t al elemento que se ubica en la posición p.
template <typename T>
void collSetAt(Coll<T>& c,T t,int p,string tToString(T)) 
{
   setTokenAt(c.s,c.sep,tToString(t),p);
}

// Retorna el elemento que se ubica en la posición p de la colección c.
template <typename T>
T collGetAt(Coll<T> c,int p,T tFromString(string)) 
{
   T t=tFromString(getTokenAt(c.s,c.sep,p));
   return t;
}

// Determina si la colección c contiene al elemento k. (devuelve la posicion)
template <typename T, typename K>
int collFind(Coll<T> c,K k,int cmpTK(T,K),T tFromString(string)) 
{  
   int cantTokens=tokenCount(c.s,c.sep);
   int pos=-1;
   for(int i=0;i<cantTokens;i++)
   {
      string token=getTokenAt(c.s,c.sep,i);
      T tToken=tFromString(token);
      if(cmpTK(tToken,k)==0)
      {
         pos=findToken(c.s,c.sep,token);
         i=cantTokens; // *
      }
   }

   return pos;
}

// Ordena los elementos de la colección c según el criterio de precedencia que establece cmpTT.
template <typename T>
void collSort(Coll<T>& c,int cmpTT(T,T),T tFromString(string),string tToString(T)) 
{
   int cantTokens = tokenCount(c.s,c.sep);  
   int i=0, j=1;
   
   while(i<cantTokens)
   {
      while(j<cantTokens)
      {
         string sToken1 = getTokenAt(c.s,c.sep,i); // 11 Juan
         string sToken2 = getTokenAt(c.s,c.sep,j); // 10 Pedro
         T token1 = tFromString(sToken1);
         T token2 = tFromString(sToken2);
         if(cmpTT(token1,token2)>0)
         {
            setTokenAt(c.s,c.sep,sToken2,i);
            setTokenAt(c.s,c.sep,sToken1,j);
         }
         j++;
      }
      i++;
      j=i+1;
   }
   
}

// Retorna true o false según queden, en la colección c, más elementos para continuar iterando.
template<typename T>
bool collHasNext(Coll<T> c) 
{
   bool ret=false;
   int cantTokens = tokenCount(c.s,c.sep);
   if(c.point<cantTokens)
   {
      ret=true;
   }
   return ret;
}

// Retorna el próximo elemento de la colección c.
template<typename T>
T collNext(Coll<T>& c,T tFromString(string)) 
{
   string token = getTokenAt(c.s,c.sep,c.point);
   T t = tFromString(token);
   c.point++;
   return t;
}

// Retorna el próximo elemento de la colección c, indicando si se llegó al final de la colección. De este modo, permite prescindir de usar collHasNext.
template<typename T>
T collNext(Coll<T>& c,bool& endOfColl,T tFromString(string)) 
{
   string token = getTokenAt(c.s,c.sep,c.point);
   T t = tFromString(token);
   endOfColl = collHasNext(c);
   if(endOfColl==false)
   {
      c.point++;
   }
   
   return t;
}

// Reinicia la colección c para que la podamos volver a iterar.
template<typename T>
void collReset(Coll<T>& c) 
{
   c.point=0;
}

template<typename T>
string collToString(Coll<T> c)
{
	return c.sep+c.s;
}

template<typename T>
Coll<T> collFromString(string s)
{
	Coll<T> c;
	c.sep=s[0];
	c.s=substring(s,1);
	return c;
}



#endif
