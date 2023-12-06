#ifndef _TARR_BITWRITER_
#define _TARR_BITWRITER_

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include "../funciones/strings.hpp"
#include "../funciones/files.hpp"

using namespace std;

struct BitWriter
{
   FILE* f;
   string sBin;
};

// Crea e inicializa una variable tipo BitWriter.
BitWriter bitWriter(FILE* f)
{
   return {f,""};
}

// Graba un bit en el archivo
void bitWriterWrite(BitWriter& bw,int bit)
{
   bw.sBin+=intToString(bit);
}

// Graba en el archivo los unos y ceros que contiene bits.
void bitWriterWrite(BitWriter& bw,string bits)
{
   bw.sBin+=bits;
}

// Indica que ya no se grabarán más bits en el archivo. 
// En el caso de que la cantidad de bits que grabamos no sea múltiplo de 8, completará con ceros a la derecha tantos bits como sea necesario, y los grabará.
void bitWriterFlush(BitWriter& bw)
{
   int bwLength = length(bw.sBin);
   while(bwLength%8 != 0)
   {
      bw.sBin+="0";
      bwLength++;
   }
   //bw.sBin=rpad(bw.sBin,8,'0');
   for(int i=0;i<bwLength;i+=8)
   {
      unsigned int b=stringToInt(substring(bw.sBin,i,i+8),2);
      unsigned char c=b;
      write<unsigned char>(bw.f,c);
   }
   bw.sBin="";
}

#endif
