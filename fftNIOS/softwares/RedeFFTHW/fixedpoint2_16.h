/*
 * fixedpoint2_16.h
 *
 *  Created on: 26/01/2012
 *      Author: Danilo
 */

#ifndef FIXEDPOINT2_16_H_
#define FIXEDPOINT2_16_H_

typedef union FIXED2_16tag {
    long full;
    struct part2_16tag {
        long fraction: 16;
        long integer: 2;
    } part;
} FIXED2_16;

char BitTest(unsigned int test, int pos);
void FIXED2_16toBinary(FIXED2_16 fixo, char* binario);
void imprimeFIXED2_16(char * s, FIXED2_16 a);
FIXED2_16 soma2_16(FIXED2_16 a, FIXED2_16 b);
FIXED2_16 sub2_16(FIXED2_16 a, FIXED2_16 b);
FIXED2_16 mult2_16(FIXED2_16 a, FIXED2_16 b);
FIXED2_16 real2FIXED2_16(float R);
float FIXED2_16toReal(FIXED2_16 F);

#endif /* FIXEDPOINT2_16_H_ */
