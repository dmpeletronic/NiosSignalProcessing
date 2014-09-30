/*
 * simpleDFT.h
 *
 *  Created on: 17/10/2011
 *      Author: Danilo
 */

#ifndef SIMPLEDFT_H
#define SIMPLEDFT_H

#define TAM 8
//#define LOGTAM 3
#define SIZE_TABLE 1024
#define DATASIZE 128
#define NUM_ITERATIONS 1000
#define NUM_POINTS 256       /* Don't touch (input data size) */
#define FFT_SIZE 8           /* Don't touch, this is log2(NUM_POINTS) */
#define PRESCALE 15
#define BUTTERFLY_SCALE_FACTOR 15

/* Here is macro to bit reverse an char */
#define bitrev(b) (((b)<<7)&0x80) |  \
      (((b)<<5)&0x40) |  \
      (((b)<<3)&0x20) |  \
      (((b)<<1)&0x10) |  \
      (((b)>>1)&0x08) |  \
      (((b)>>3)&0x04) |  \
      (((b)>>5)&0x02) |  \
      (((b)>>7)&0x01)

typedef struct
{
       float real;
       float imag;
}COMPLEXO ;

void dft(COMPLEXO in_data[DATASIZE], COMPLEXO out_data[DATASIZE], unsigned int inverse, unsigned int N);
void dft_tabled(COMPLEXO in_data[DATASIZE], COMPLEXO out_data[DATASIZE], unsigned int inverse, unsigned int N, double sin_table [DATASIZE][DATASIZE], double cos_table[DATASIZE][DATASIZE]);
void imprime(COMPLEXO * d, int size, char * titulo);

void fft(int n, COMPLEXO dado[], int LOGTAM);
int reverse_bits(unsigned int i, int n);
void software_only_fft2(alt_16 *InData, alt_16 *OutData, alt_16 *TwiddleTable);

//FFT by egon
void FFT_Egon(COMPLEXO dado[], int nptos);
void Reordem(COMPLEXO dado[], int nptos);
void CarregaTabw(int nptos);
void ColTuk(COMPLEXO dado[], int nptos);

void copy_data_to_complex(short * data, int size, COMPLEXO * dados);
void copy_complex_to_data(COMPLEXO * dados, int size, short * data);
void copy_complex_to_complex(COMPLEXO *in, int size, COMPLEXO *out);
float soma_real_imag(COMPLEXO * dados);
void init_sincos_table(double sin_table[DATASIZE][DATASIZE], double cos_table[DATASIZE][DATASIZE], int N);



#endif /* SIMPLEDFT_H */





