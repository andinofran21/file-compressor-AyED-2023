#ifndef _TARR_BITREADER_
#define _TARR_BITREADER_

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include "../funciones/strings.hpp"
#include "../funciones/files.hpp"

using namespace std;

struct BitReader
{
   FILE* f;
   unsigned char c;
   int pos;
};

BitReader bitReader(FILE* f)
{
   return {f,0};
}

string _binToString(unsigned char c)
{
   int i=0;
   string sBin = "";
   while(i<8)
   {
      unsigned char byte1=c<<i;
      unsigned char byte2=byte1>>7;
      sBin+=intToString(byte2);
      i++;
   }
   return sBin;
}

int bitReaderRead(BitReader& br)
{
   int bit;
   if(br.pos==0)
   {
      br.c=read<unsigned char>(br.f);
      //seek<unsigned char>(br.f,0);
   }

   string sBin = _binToString(br.c);
   bit=charToInt(sBin[br.pos]);
   br.pos<7?br.pos++:br.pos=0;

   return bit;
}

#endif
