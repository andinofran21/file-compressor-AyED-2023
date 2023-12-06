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
   string buf;
};

BitWriter bitWriter(FILE* f)
{
   BitWriter b;
   b.f = f;
   b.buf = "";
   return b;
}

char _stringBinToDec(string decS)
{
   unsigned int dec = 0;
   int cant = length(decS), pot=128;
   for(int i=0;i<cant;i++)
   {
      dec += charToInt((char)decS[i])*pot;
      pot=pot/2;
   }

   return dec;
}

void bitWriterWrite(BitWriter& bw,int bit)
{
   char byte;

   bw.buf+=intToString(bit);

   if(length(bw.buf)==8)
   {
      byte = _stringBinToDec(bw.buf);
      write<char>(bw.f,byte);
      bw.buf="";
   }
}

void bitWriterWrite(BitWriter& bw,string sbit)
{
   int cant = length(sbit);
   for(int i=0;i<cant;i++)
   {
      bitWriterWrite(bw,charToInt((char)sbit[i]));
   }
}

void bitWriterFlush(BitWriter& bw)
{
   char byte;
   int i = length(bw.buf);
   if(bw.buf!="")
   {
      while(i<8)
      {
         bw.buf+="0";
         i++;
      }
      byte = _stringBinToDec(bw.buf);
      write<char>(bw.f,(char)byte);
   }
   bw.buf="";
}

#endif
