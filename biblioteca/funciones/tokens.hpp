#ifndef _TTOKENS_T_
#define _TTOKENS_T_

#include <iostream>
#include <stdio.h>
#include "strings.hpp"
using namespace std;

// Cuenta la cantidad tokens que el separador sep genera en s.
int tokenCount(string s,char sep) 
{
   int ret = 0;
   if(s!="")
   {
      ret=charCount(s,sep) + 1;
   }
   
   return ret;
}

// Agrega el token t al final de la cadena s.
void addToken(string& s,char sep,string t) 
{
   if(s=="")
   {
      s+=t;
   }
   else
   {
      s+=sep+t;
   }
}

// Retorna el i-ésimo token de la cadena tokenizada s
string getTokenAt(string s,char sep, int i) 
{
   int sep1=indexOfN(s,sep,i);
   int sep2=indexOfN(s,sep,i+1);
   string token = substring(s,sep1+1,sep2);
   return token;
}

// Remueve de s el token ubicado en la posición i (0-1-2...).
void removeTokenAt(string& s,char sep, int i) 
{
   int sep1=indexOfN(s,sep,i);
   int sep2=indexOfN(s,sep,i+1);
   string newS="";
   if(i==0)
   {
      if(tokenCount(s,sep)==1)
      {
         newS="";
      }
      else
      {
         newS+=substring(s,sep2+1);
      }
   }
   else
   {
      newS+=substring(s,0,sep1);
      newS+=substring(s,sep2);
   }
   s=newS;
   
   //ZOE MANCINI
   /* int j=0;
   int contador=0;
   while(j<length(s)){
      if (s[j]==sep){
         contador++;
      }
      if (contador==i){
         do {
            s=removeAt(s,j);
         }while(s[j]!=sep && j<length(s));
         contador++;
      }
      j++;
   }
   if(startsWith(s,"|")){
      s=removeAt(s,0);
   } */
}

// Reemplaza por t el token de s ubicado en la posición i.
void setTokenAt(string& s,char sep, string t,int i) 
{
   int sep1=indexOfN(s,sep,i);
   int sep2=indexOfN(s,sep,i+1);
   string newS="";
   newS+=substring(s,0,sep1+1);
   newS+=t;
   newS+=substring(s,sep2);
   s=newS;
}

//Determinar la posición que el token t ocupa dentro de la cadena s.
int findToken(string s,char sep, string t) 
{
   int cantToken=tokenCount(s,sep);
   int pos=-1;
   for(int i=0;i<cantToken;i++)
   {
      if(getTokenAt(s,sep,i)==t)
      {
         pos=i;
         i=cantToken;
      }
   }
   return pos;
}

#endif
