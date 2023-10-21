#ifndef _TSTRINGS_T_
#define _TSTRINGS_T_

#include <iostream>
#include <stdio.h>
#include <math.h>
using namespace std;

//longitud de una cadena 
int length(string s) 
{
   int i=0;
   while(s[i]!='\0')
   {
      i++;
   }

   return i;
}

//cantidad de veces que aparece c en s 
int charCount(string s,char c) 
{
   int i=0, cant=0;
   while(s[i]!='\0')
   {
      if(s[i]==c)
      {
         cant++;
      }
      i++;
   }
   return cant;
}

//subcadena desde d a h(noinclusive) 
string substring(string s,int d,int h) 
{
   string subcadena="";
   for(d;d<h;d++)
   {
      subcadena+=s[d];
   }
   return subcadena;
}

// subcadena desde d hasta el final 
string substring(string s,int d) 
{
   string subcadena="";
   while(s[d]!='\0')
   {
      subcadena+=s[d];
      d++;
   }
   return subcadena;
}

// posicion de la primera coincidencia de c (r)
int indexOf(string s,char c) 
{
   int i=0, pos=-1;
   /* while(s[i]!='\0')
   {
      if(s[i]==c)
      {
         pos=i;
         i=length(s)-1;
      }
      i++;
   } */
   for(i;s[i]!='\0';i++)
   {
      if(s[i]==c)
      {
         pos=i;
         s[i+1]='\0';
      }
   }
   return pos;
}

// posicion de la primera coincidencia de c desde offSet ()
int indexOf(string s,char c,int offSet) 
{
   int i=offSet, pos=-1;
   /* while(s[i]!='\0')
   {
      if(s[i]==c)
      {
         pos=i;
         i=length(s)-1;
      }
      i++;
   } */
   for(i;s[i]!='\0';i++)
   {
      if(s[i]==c)
      {
         pos=i;
         s[i+1]='\0';
      }
   }
   return pos;
}

// pos de la primera ocurrencia de toSearch en s 
int indexOf(string s,string toSearch) 
{
   int i=0, pos=-1;
   int j=length(toSearch);
   for(i;s[i]!='\0';i++, j++)
   {
      string sub = substring(s,i,j);
      if(sub==toSearch)
      {
         pos=i;
         s[i+1]='\0';
      }
   }
   return pos;
}

// idem desde offset (ok)
int indexOf(string s,string toSearch,int offset) 
{
   int i=offset, pos=-1;
   int j=length(toSearch) + i;

   for(i;s[i]!='\0';i++, j++)
   {
      string sub = substring(s,i,j);
      if(sub==toSearch)
      {
         pos=i;
         s[i+1]='\0';
      }
   }
   return pos;
}

//posicion de la ultima ocurrencia de c 
int lastIndexOf(string s,char c) 
{
   int i=length(s), pos=-1;
   for(i;i!=0;i--)
   {
      if(s[i]==c)
      {
         pos=i;
         i=1;
      }
   }
   return pos;
}

// posición de la n-ésima ocurrencia de c dentro de s
int indexOfN(string s,char c,int n) 
{
   int offset=0, pos=-1;
   int cantConcurr=charCount(s,c);

   if(0<n && n<=cantConcurr)
   {
      for(int i=0;i!=n;i++)
      {
         pos=indexOf(s,c,offset);
         offset=pos+1;
      }
   }
   else
   {
      if(n>cantConcurr)
      {
         pos=length(s);
      }
   }

   return pos;
}

// valor numerico que representa c ('A'=10)
int charToInt(char c) 
{
   int ret=c;
   
   if('A'<=c && c<='Z')
   {
      ret -= 55; //65=primer C.ASCCI
   }
   else
   {
      if('a'<=c && c<='z')
      {
         ret -= 87; //97=primer C.ASCCI
      }
      else  
      {
         if('0'<=c && c<='9')
         {
            ret -= 48; //48=primer C.ASCCI
         }
      }
   }
   return ret;
}

// valor alfabetico que representa i (65='A')
char intToChar(int i) 
{
   char ret;
   if (i>=65 && i<=90)
   {
      ret=i;
   }
   else
   {
      if(i>=0 && i<=9)
      {
         ret=i+48;
      }
      // else agregado 6/9/2023 
      else 
      {
         if(i>=48 && i<=57)
         {
            ret=i;
         }
      }
   }
   
   return ret;
}

//i-ésimo dígito del valor de n. (de derecha (0) a izquierda)
int getDigit(int n,int i) 
{
   int get=10, descart=1;
   int ret;
   for(int j=0;j<i;j++)
   {
      get*=10;
      descart*=10;
   }
   ret = (n%get) / descart;
   return ret;
}

// contador de digitos (int)
int digitCount(int n) 
{
   int cont=1, ret=0;
   while(cont<=n || (n==0 && cont<10))
   {
      cont*=10;
      ret++;
   }
   return ret;
}

//de entero a cadena
string intToString(int i) 
{
   int pos=digitCount(i)-1;
   int digit;
   string ret="";
   while(pos>=0)
   {
      digit=getDigit(i,pos);
      ret+=intToChar(digit);
      pos--;
   }
   return ret;
}

// de cadena (entero en base b) a decimal (PERFECTO)
int stringToInt(string s,int b) 
{
   int num;
   int pos=length(s)-1;
   /* int cantDigit=length(s); */
   int ret=0;
   for(int i=0;s[i]!='\0';i++) //456
   {
      num=charToInt(s[i]);
      ret+=num*pow(b,pos); //pow funcion de potencia
      pos--;
   }
   
   return ret;
}

// String de numeros decimales a entero
int stringToInt(string s) 
{
   int ret=0;
   int potencia=length(s)-1;
   for(int i=0;s[i]!='\0';i++)
   {
      ret+=charToInt(s[i])*pow(10,potencia);
      potencia--;
   }
   return ret;
}

//de char a string (un solo caracter)
string charToString(char c) 
{
   string ret;
   ret=c;
   return ret;
}

// de string a char   (un solo caracter)
char stringToChar(string s)
{
   char ret;
   ret=s[0];
   return ret;
}

// funcion trivial
string stringToString(string s) 
{
   string ret=s;
   return ret;
}

// de double a string (reducido a 2 decimales)
string doubleToString(double d) 
{
   /* string ret;
   int entero=d;
   int residuo=(d-entero)*100;
   int j=digitCount(d)-1;
   for(j;j>=0;j--)
   {
      int digit=getDigit(d,j);
      ret+=intToChar(digit);
   }
   ret+='.';
   for(int i=0;i<2;i++)
   {
      int digit=getDigit(residuo,1-i);
      ret+=intToChar(digit);
   } */
   int entero=d;
   int residuo = (d-entero)*100;
   string ret=intToString(entero);
   ret+='.';
   for(int i=0;i<2;i++)
   {
      int digit=getDigit(residuo,1-i);
      ret+=intToChar(digit);
   }
   return ret;
}

// de string a double
double stringToDouble(string s)
{
   double ret=stringToInt(s);
   int residuo=0;
   string aux="";
   int i=0;
   while(s[i]!='\0')
   {
      if(s[i]=='.')
      {
         aux+=s[i];
      }
      i++;
   }
   residuo=stringToInt(aux);
   ret+=residuo;
   return ret;
}

//true si la cadena es vacia ("" != "  ")
bool isEmpty(string s) 
{
   bool ret=false;
   if(s=="")
   {
      ret=true;
   }
   return ret;
}

// true si x es prefijo de s
bool startsWith(string s,string x) 
{
   bool ret=false;
   int xLength = length(x);
   
   if(substring(s,0,xLength)==x)
   { 
      ret=true;
   }
   
   return ret;
}

// true si x es sufijo de s
bool endsWith(string s,string x) 
{
   bool ret=false;
   int xLength = length(x);
   int sLength = length(s);
   
   if(substring(s,sLength-xLength,sLength)==x)
   { 
      ret=true;
   }
   return ret;
}

// true si s contiene a c
bool contains(string s,char c) 
{
   bool ret=false;
   if(indexOf(s,c)!=-1)
   {
      ret=true;
   }

   return ret;
}

// Reemplaza en s todas las ocurrencias de oldChar por newChar.
string replace(string s,char oldChar,char newChar)
{
   int pos=0;
   int match=indexOf(s,oldChar,pos);
   while(match!=-1 )
   {
      s[match]=newChar;
      pos=match;
      match=indexOf(s,oldChar,pos);
   }
   return s;
}

// Inserta caractes c en la posicion pos 
string insertAt(string s,int pos,char c) 
{
   /* string add = substring(s,pos);
   s[pos]=c; */

   string newString=substring(s,0,pos);
   newString+=c;
   newString+=substring(s,pos);

   return newString;
}

// elimina el caracter de la posicion pos
string removeAt(string s,int pos) 
{
   string newString=substring(s,0,pos);
   newString+=substring(s,pos+1);
   return newString;
}

// Quita los espacios sobrantes de la izquierda
string ltrim(string s) 
{
   /* int i = 0;
   string resultado="";
   while(s[i] != '\0'){
      if(s[i] != ' '){
         resultado=substring(s,i);
         s[i+1]='\0';
      }
      i++;
   } */
   string ret="";
   for(int i=0;s[i]!='\0';i++)
   {
      if(s[i]!=' ')
      {
         ret=substring(s,i);
         s[i+1]='\0';
      }
   }
   return ret;
}

// Quita los espacios sobrantes de la derecha
string rtrim(string s) 
{
   /* string resultado="";
   int i=length(s)-1;
   if(s[i]!=' ')
   {
      resultado=s;
   }
   else
   {
      for(i;s[i]==' ';i--)
      {
         resultado=substring(s,0,i);
      }
   } */
   string ret="";
   int i=length(s)-1;
   for(i;s[i]!='\0';i--)
   {
      if(s[i]!=' ')
      {
         ret=substring(s,0,i+1);
         s[i-1]='\0';
      }
   }
   return ret;
}

// Quita los espacios sobrantes a izquierda y derecha
string trim(string s) 
{
   string ret="";
   ret=ltrim(s);
   ret=rtrim(ret);
   return ret;
}

// Genera una cadena de caracteres compuesta por n caracteres c.
string replicate(char c,int n) 
{
   string ret="";
   for(int i=0;i<n;i++)
   {
      ret+=c;
   }
   return ret;
}

// Genera una cadena de caracteres compuesta por n caracteres ' '
string spaces(int n) 
{
   string ret="";
   for(int i=0;i<n;i++)
   {
      ret+=' ';
   }
   return ret;
}

// genera con caracteres c hasta completar el espacio n a izquierda (si fuese necesario)
string lpad(string s,int n,char c) 
{
   string ret="";
   int slength=length(s);
   if(slength<n)
   {
      ret=replicate(c,n-slength);
      ret+=s;
   }
   else
   {
      ret=s;
   }
   
   return ret;
}

// genera con caracteres c hasta completar el espacio n a derecha (si fuese necesario)
string rpad(string s,int n,char c) 
{
   string ret="";
   int slength=length(s);
   if(slength<n)
   {
      ret=s;
      ret+=replicate(c,n-slength);
   }
   else
   {
      ret=s;
   }
   
   return ret;
}

// Completa y distribuye con caracteres c a izquierda y derecha.
string cpad(string s,int n,char c) 
{
   string ret="";
   int slength=length(s);
   int add=n-slength;
   ret+=replicate(c,(add/2));
   ret+=s;
   if(add%2==1)   
   {
      ret+=replicate(c,(add/2)+1);
   }
   else
   {
      ret+=replicate(c,(add/2));
   }

   return ret;
}

// Determina si el valor de c corresponde o no a un dígito numérico
bool isDigit(char c) 
{
   bool ret=false;
   if(48<=c && c<=57)
   {
      ret=true;
   }
   return ret;
}

// Determina si el valor de c corresponde o no a una letra.
bool isLetter(char c) 
{
   bool ret=false;
   if((65<=c && c<=90) || (97<=c && c<=122))
   {
      ret=true;
   }
   return ret;
}

// Determina si el valor de c corresponde a una letra mayúscula.
bool isUpperCase(char c) 
{
   bool ret=false;
   if(65<=c && c<=90)
   {
      ret=true;
   }
   return ret;
}

// Determina si el valor de c corresponde a una letra minúscula.
bool isLowerCase(char c) 
{
   bool ret=false;
   if(97<=c && c<=122)
   {
      ret=true;
   }
   return ret;
}

// Convierte el valor de c a mayúscula.
char toUpperCase(char c) 
{
   char ret=c;
   if(97<=c && c<=122)
   {
      ret-=32;
   }
   return ret;
}

// Convierte el valor de c a minúscula.
char toLowerCase(char c) 
{
   char ret=c;
   if(65<=c && c<=90)
   {
      ret+=32;
   }
   return ret;
}

// Retorna una cadena idéntica a s pero completamente en mayúsculas
string toUpperCase(string s) 
{
   int i=0;
   string ret="";
   while(s[i]!='\0')
   {
      ret+=toUpperCase(s[i]);
      i++;
   }
   return ret;
}

// Retorna una cadena idéntica a s pero completamente en minúsculas
string toLowerCase(string s) 
{
   int i=0;
   string ret="";
   while(s[i]!='\0')
   {
      ret+=toLowerCase(s[i]);
      i++;
   }
   return ret;
}

// Compara alfabéticamente dos cadenas.
int cmpString(string a,string b) 
{
   int ret=1;
   if(a<b)
   {
      ret=-1;
   }
   else
   {
      if(a==b)
      {
         ret=0;
      }
   }
   return ret;
}

// Compara dos valores.
int cmpDouble(double a,double b) 
{
   int ret=1;
   if(a<b)
   {
      ret=-1;
   }
   else
   {
      if(a==b)
      {
         ret=0;
      }
   }
   return ret;
}

#endif
