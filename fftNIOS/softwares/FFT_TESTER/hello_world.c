/*
 * "Hello World" example.
 *
 * This example prints 'Hello from Nios II' to the STDOUT stream. It runs on
 * the Nios II 'standard', 'full_featured', 'fast', and 'low_cost' example
 * designs. It runs with or without the MicroC/OS-II RTOS and requires a STDOUT
 * device in your system's hardware.
 * The memory footprint of this hosted application is ~69 kbytes by default
 * using the standard reference design.
 *
 * For a reduced footprint version of this template, and an explanation of how
 * to reduce the memory footprint for a given application, see the
 * "small_hello_world" template.
 *
 */

#include "alt_types.h"
#include "system.h"
#include "math.h"
#include "fft_pipeline_.h"
#include "fixedpoint2_16.h"
#include "altera_avalon_performance_counter.h"
#include <stdio.h>

#define PI		3.14159265358979323846
    FIXED2_16 vetor[1024];

void caso_teste(void);

int delay(int i){
	int j = 1000;
	while(i-->0){
		while(j-->0);
	}

	return 0;
}


int main()
{
	int i,j=0;
	int rx_char=0;
	int estado= 0;
    char line[100]="";

    FIXED2_16 dado;
    int Nps, N, NS, T;
    float dt,  t = 0, y, F;

    printf("Nios is alive!\n");
    N = 256;
	NS = 16;
	Nps = N/NS;
	T = 1;
	dt= ((float) T)/((float)(NS*Nps));
	F= (float)NS/(float)T;
	t = 0;
	printf("Inicializando sinal... \n");
	for(i=0; i < N/*1023*/; i++){
			  y = sin(t*2*PI*F) / 1000;
			  t=t+dt;
			  dado = real2FIXED2_16(y);
			  vetor[i] = dado;
	 }

    while(1){

			printf("Informe o delay: ");

			rx_char = getchar();
			fgets(line, sizeof(line), stdin);
			//sscanf(line, "%d" , &rx_char);
			printf("\nrx_char=%d", rx_char);
			if(rx_char == '0'){

				estado = FFT_FINISHED();
				printf("Estado FFT: %d\n", estado);
				printf("Inicializando FFT... \n");

				caso_teste();
			}
/*
			for(i=0; i<N; i++){
					//printf("%f ", FIXED2_16toReal(vetor[i]));
					FFT_ESCREVE_DADO(i, vetor[i].full);
			}*/
			//printf("Executando FFT!  \n");
			//estado = FFT_FINISHED();
			//printf("Estado FFT: %d\n", estado);
			//FFT_START();
			//estado = FFT_FINISHED();
		  //  printf("Estado FFT: %d\n", estado);
		  //  delay(rx_char);
		 //   estado = FFT_FINISHED();
		 //   printf("Estado FFT: %d\n", estado);
		  //  for(i=0; i<8*N; i++){
		    //	  dado.full =  FFT_LE_DADO(i);
		    //	  printf("%d: %f\n", i, FIXED2_16toReal(dado));
		 //   }

	}
  return 0;
}


void caso_teste(void){

	int i,j;
	FIXED2_16 vetorXreal[256], vetorXimag[256];
	FIXED2_16 ponto;


	PERF_RESET(PERFORMANCE_COUNTER_BASE);
	PERF_START_MEASURING(PERFORMANCE_COUNTER_BASE);
	PERF_BEGIN (PERFORMANCE_COUNTER_BASE, 1);

	for(i=0; i<256; i++){
			    ponto = vetor[i];
				FFT_ESCREVE_DADO(i, ponto.full);
	}
	PERF_END (PERFORMANCE_COUNTER_BASE, 1);
	i=0;

	FFT_START();
	PERF_BEGIN (PERFORMANCE_COUNTER_BASE, 2);


	while(FFT_FINISHED() == 0){
				if(i++>100000)break;
		//i++;
		}
	PERF_END (PERFORMANCE_COUNTER_BASE, 2);
	printf("\ni = %d", i);

	PERF_BEGIN (PERFORMANCE_COUNTER_BASE, 3);
	#define real1base 0
	#define imag1base 512
	#define real2base 1024
	#define imag2base 1536
	j=0;
	for(i=0; i<256; i+=2){
			vetorXreal[i].full = FFT_LE_DADO(j+real1base);
			vetorXreal[i+1].full = FFT_LE_DADO(j+real2base);
			vetorXimag[i].full = FFT_LE_DADO(j+imag1base);
			vetorXimag[i+1].full = FFT_LE_DADO(j+imag2base);
			j++;
	}
	PERF_END (PERFORMANCE_COUNTER_BASE, 3);
	PERF_STOP_MEASURING(PERFORMANCE_COUNTER_BASE);
    perf_print_formatted_report((void *)PERFORMANCE_COUNTER_BASE,
	   ALT_CPU_FREQ, 3,  "Envio dos dados", "Executa FFT", "Leitura dados");

}
