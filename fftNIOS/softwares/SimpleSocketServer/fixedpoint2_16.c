/*
 * fixedpoint2_16.c
 *
 *  Created on: 26/01/2012
 *      Author: Danilo
 */
#include "fixedpoint2_16.h"

char BitTest(unsigned int test, int pos){

     char bit=0;

     bit = (test>>pos)&0x01;

     return bit;
}

void FIXED2_16toBinary(FIXED2_16 fixo, char* binario){
     int i=0, j=0;
     char bin[33];
     j=0;
     for(i=17; i>=0; i--){
               if(BitTest(fixo.full, i)){
                     bin[j]='1';
               }else{
                     bin[j]='0';
               }
               j++;
     }
     bin[j]='\0';
     sprintf(binario, bin);
}

void imprimeFIXED2_16(char * s, FIXED2_16 a){
     long integer=0, fraction=0, full=0;

     full = (a.full & 0x3FFFF);
     integer = (a.part.integer) & 0x3;
     fraction = (a.part.fraction) & 0xFFFF;
     printf("\n%s = %x.%04x ou %04x", s, integer, fraction, full);
}

FIXED2_16 soma2_16(FIXED2_16 a, FIXED2_16 b){
         FIXED2_16 temp;
         temp.full = a.full + b.full;
         return temp;
}
FIXED2_16 sub2_16(FIXED2_16 a, FIXED2_16 b){
         FIXED2_16 temp;
         temp.full = a.full - b.full;
         return temp;
}
FIXED2_16 mult2_16(FIXED2_16 a, FIXED2_16 b){
         FIXED2_16 temp;
         long long i;
        // printf("\n\nA= %04x * B= %04x", a.full, b.full);
         i = ((long long)a.full * (long long)b.full + 2^15)>>16;
         temp.full = (int) i;
         return temp;
}

FIXED2_16 real2FIXED2_16(float R){

         FIXED2_16 temp;
         temp.full=(int)(R * (1<<16) + (R>=0 ? 0.5 : -0.5));
         return temp;
}

float FIXED2_16toReal(FIXED2_16 F){
      float res=0.0;

      res = (float)F.full / (1<<16);
      return res;
}

