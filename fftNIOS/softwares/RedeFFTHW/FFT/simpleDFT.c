#include <alt_types.h>
#include "simpleDFT.h"
#include <math.h>
#include <float.h>  /* FLT_MAX */

float cos_table[] = {1.000000, 0.999981, 0.999925, 0.999831, 0.999699, 0.999529, 0.999322, 0.999078,
                     0.998795, 0.998476, 0.998118, 0.997723, 0.997290, 0.996820, 0.996313, 0.995767,
                     0.995185, 0.994565, 0.993907, 0.993212, 0.992480, 0.991710, 0.990903, 0.990058,
                     0.989177, 0.988258, 0.987301, 0.986308, 0.985278, 0.984210, 0.983105, 0.981964,
                     0.980785, 0.979570, 0.978317, 0.977028, 0.975702, 0.974339, 0.972940, 0.971504,
                     0.970031, 0.968522, 0.966976, 0.965394, 0.963776, 0.962121, 0.960431, 0.958703,
                     0.956940, 0.955141, 0.953306, 0.951435, 0.949528, 0.947586, 0.945607, 0.943593,
                     0.941544, 0.939459, 0.937339, 0.935184, 0.932993, 0.930767, 0.928506, 0.926210,
                     0.923880, 0.921514, 0.919114, 0.916679, 0.914210, 0.911706, 0.909168, 0.906596,
                     0.903989, 0.901349, 0.898674, 0.895966, 0.893224, 0.890449, 0.887640, 0.884797,
                     0.881921, 0.879012, 0.876070, 0.873095, 0.870087, 0.867046, 0.863973, 0.860867,
                     0.857729, 0.854558, 0.851355, 0.848120, 0.844854, 0.841555, 0.838225, 0.834863,
                     0.831470, 0.828045, 0.824589, 0.821102, 0.817585, 0.814036, 0.810457, 0.806848,
                     0.803208, 0.799537, 0.795837, 0.792107, 0.788346, 0.784557, 0.780737, 0.776888,
                     0.773010, 0.769103, 0.765167, 0.761202, 0.757209, 0.753187, 0.749136, 0.745058,
                     0.740951, 0.736817, 0.732654, 0.728464, 0.724247, 0.720003, 0.715731, 0.711432,
                     0.707107, 0.702755, 0.698376, 0.693971, 0.689541, 0.685084, 0.680601, 0.676093,
                     0.671559, 0.667000, 0.662416, 0.657807, 0.653173, 0.648514, 0.643832, 0.639124,
                     0.634393, 0.629638, 0.624860, 0.620057, 0.615232, 0.610383, 0.605511, 0.600616,
                     0.595699, 0.590760, 0.585798, 0.580814, 0.575808, 0.570781, 0.565732, 0.560662,
                     0.555570, 0.550458, 0.545325, 0.540171, 0.534998, 0.529804, 0.524590, 0.519356,
                     0.514103, 0.508830, 0.503538, 0.498228, 0.492898, 0.487550, 0.482184, 0.476799,
                     0.471397, 0.465977, 0.460539, 0.455084, 0.449611, 0.444122, 0.438616, 0.433094,
                     0.427555, 0.422000, 0.416430, 0.410843, 0.405241, 0.399624, 0.393992, 0.388345,
                     0.382683, 0.377007, 0.371317, 0.365613, 0.359895, 0.354164, 0.348419, 0.342661,
                     0.336890, 0.331106, 0.325310, 0.319502, 0.313682, 0.307850, 0.302006, 0.296151,
                     0.290285, 0.284408, 0.278520, 0.272621, 0.266713, 0.260794, 0.254866, 0.248928,
                     0.242980, 0.237024, 0.231058, 0.225084, 0.219101, 0.213110, 0.207111, 0.201105,
                     0.195090, 0.189069, 0.183040, 0.177004, 0.170962, 0.164913, 0.158858, 0.152797,
                     0.146730, 0.140658, 0.134581, 0.128498, 0.122411, 0.116319, 0.110222, 0.104122,
                     0.098017, 0.091909, 0.085797, 0.079682, 0.073565, 0.067444, 0.061321, 0.055195,
                     0.049068, 0.042938, 0.036807, 0.030675, 0.024541, 0.018407, 0.012272, 0.006136,
                     0.000000};

float sin_table[] = {0.000000, -0.006136, -0.012272, -0.018407, -0.024541, -0.030675, -0.036807, -0.042938,
                     -0.049068, -0.055195, -0.061321, -0.067444, -0.073565, -0.079682, -0.085797, -0.091909,
                     -0.098017, -0.104122, -0.110222, -0.116319, -0.122411, -0.128498, -0.134581, -0.140658,
                     -0.146730, -0.152797, -0.158858, -0.164913, -0.170962, -0.177004, -0.183040, -0.189069,
                     -0.195090, -0.201105, -0.207111, -0.213110, -0.219101, -0.225084, -0.231058, -0.237024,
                     -0.242980, -0.248928, -0.254866, -0.260794, -0.266713, -0.272621, -0.278520, -0.284408,
                     -0.290285, -0.296151, -0.302006, -0.307850, -0.313682, -0.319502, -0.325310, -0.331106,
                     -0.336890, -0.342661, -0.348419, -0.354164, -0.359895, -0.365613, -0.371317, -0.377007,
                     -0.382683, -0.388345, -0.393992, -0.399624, -0.405241, -0.410843, -0.416430, -0.422000,
                     -0.427555, -0.433094, -0.438616, -0.444122, -0.449611, -0.455084, -0.460539, -0.465977,
                     -0.471397, -0.476799, -0.482184, -0.487550, -0.492898, -0.498228, -0.503538, -0.508830,
                     -0.514103, -0.519356, -0.524590, -0.529804, -0.534998, -0.540171, -0.545325, -0.550458,
                     -0.555570, -0.560662, -0.565732, -0.570781, -0.575808, -0.580814, -0.585798, -0.590760,
                     -0.595699, -0.600616, -0.605511, -0.610383, -0.615232, -0.620057, -0.624860, -0.629638,
                     -0.634393, -0.639124, -0.643832, -0.648514, -0.653173, -0.657807, -0.662416, -0.667000,
                     -0.671559, -0.676093, -0.680601, -0.685084, -0.689541, -0.693971, -0.698376, -0.702755,
                     -0.707107, -0.711432, -0.715731, -0.720003, -0.724247, -0.728464, -0.732654, -0.736817,
                     -0.740951, -0.745058, -0.749136, -0.753187, -0.757209, -0.761202, -0.765167, -0.769103,
                     -0.773010, -0.776888, -0.780737, -0.784557, -0.788346, -0.792107, -0.795837, -0.799537,
                     -0.803208, -0.806848, -0.810457, -0.814036, -0.817585, -0.821102, -0.824589, -0.828045,
                     -0.831470, -0.834863, -0.838225, -0.841555, -0.844854, -0.848120, -0.851355, -0.854558,
                     -0.857729, -0.860867, -0.863973, -0.867046, -0.870087, -0.873095, -0.876070, -0.879012,
                     -0.881921, -0.884797, -0.887640, -0.890449, -0.893224, -0.895966, -0.898674, -0.901349,
                     -0.903989, -0.906596, -0.909168, -0.911706, -0.914210, -0.916679, -0.919114, -0.921514,
                     -0.923880, -0.926210, -0.928506, -0.930767, -0.932993, -0.935184, -0.937339, -0.939459,
                     -0.941544, -0.943593, -0.945607, -0.947586, -0.949528, -0.951435, -0.953306, -0.955141,
                     -0.956940, -0.958703, -0.960431, -0.962121, -0.963776, -0.965394, -0.966976, -0.968522,
                     -0.970031, -0.971504, -0.972940, -0.974339, -0.975702, -0.977028, -0.978317, -0.979570,
                     -0.980785, -0.981964, -0.983105, -0.984210, -0.985278, -0.986308, -0.987301, -0.988258,
                     -0.989177, -0.990058, -0.990903, -0.991710, -0.992480, -0.993212, -0.993907, -0.994565,
                     -0.995185, -0.995767, -0.996313, -0.996820, -0.997290, -0.997723, -0.998118, -0.998476,
                     -0.998795, -0.999078, -0.999322, -0.999529, -0.999699, -0.999831, -0.999925, -0.999981,
                     -1.000000};

/*Algoritmo da FFT by Egon*/
float * Wy;
float * Wx;
void CarregaTabw(int nptos) {
	  int i;
      float teta = 2.0 * M_PI / nptos;
      Wy = (float*)malloc(sizeof(float)*nptos);
      Wx = (float*)malloc(sizeof(float)*nptos);
      for (i = 0; i < nptos / 2; i++) {
	        Wx[i] =  (float)cos((double)(teta * i));
	        Wy[i] = -1*(float)sin((double)(teta * i));
	  }
}
void Reordem(COMPLEXO dado[], int nptos){
   int rb, i;
   float t1;
   /* Aqui ocorre a reversão dos bits */
    for(i = 0; i < nptos; i++){
          rb = reverse_bits(i, nptos);
          if(i < rb){
              t1 = dado[i].real;
              dado[i].real = dado[rb].real;
              dado[rb].real = t1;
              t1 = dado[i].imag;
              dado[i].imag = dado[rb].imag;
              dado[rb].imag = t1;
          }
    }
}
/* Aplica o algoritmo da borboleta de Cooley Tukey*/
void ColTuk(COMPLEXO dado[], int nptos)
{
float  sx, sy;
int    d, db, i, k, p, q, r;
int nn = 1;
//     int fat = nptos / nptos;
      for( d=1; d < nptos; d *= 2)  {
	   db = 2 * d;
	   for( i=0; i < nptos; i += db)  {
		for( k=0; k < d; k++)  {
		     p = i + k;
		     q = p + d;
//                     r = (nptos / db * k) * fat;
		     r = (nptos / db * k);
		     nn++;
		     sx = dado[q].real * Wx[r] - dado[q].imag * Wy[r];
	         sy = dado[q].real* Wy[r] + dado[q].imag * Wx[r];
		     dado[q].real = dado[p].real - sx;
		     dado[q].imag = dado[p].imag - sy;
		     dado[p].real += sx;
		     dado[p].imag += sy;
		}
	   }
      }
}

void FFT_Egon(COMPLEXO dado[], int nptos){
	CarregaTabw(nptos);
	Reordem(dado, nptos);
	ColTuk(dado, nptos);
}


/*Algoritmo da FFT
 *
 */
void fft(int n, COMPLEXO dado[], int LOGTAM)
{
    int i, j, k, n1, n2, rb = 0, angle;
    float c, s, tetha, t1, t2;

    /* Aqui ocorre a reversão dos bits */
    for(i = 0; i < n; i++){
          rb = reverse_bits(i, n);
          if(i < rb){
              t1 = dado[i].real;
              dado[i].real = dado[rb].real;
              dado[rb].real = t1;
              t1 = dado[i].imag;
              dado[i].imag = dado[rb].imag;
              dado[rb].imag = t1;
          }
    }

    /* Aqui começa o cálculo da FFT */
    n1 = 0;
    n2 = 1;
    for(i = 0; i < LOGTAM; i++){
          n1 = n2;
          n2 += n2;
          tetha = SIZE_TABLE/n2;
          angle = 0.0;

          for(j = 0; j < n1; j++){
                if(angle <= SIZE_TABLE/4){
                    c = cos_table[angle];
                    s = sin_table[angle];
                }

                else if(angle > SIZE_TABLE/4 && angle <= SIZE_TABLE/2){
                     c = -cos_table[angle-SIZE_TABLE/4];
                     s = sin_table[angle-SIZE_TABLE/4];
                }

                else if(angle > SIZE_TABLE/2 && angle <= 3*SIZE_TABLE/4){
                     c = -cos_table[angle-SIZE_TABLE/2];
                     s = -sin_table[angle-SIZE_TABLE/2];
                }

                else if(angle > 3*SIZE_TABLE/4 && angle < SIZE_TABLE){
                     c = cos_table[SIZE_TABLE-angle];
                     s = -sin_table[SIZE_TABLE-angle];
                }

                angle += tetha;
                for(k = 0; k < n; k += n2 ){
                      t1 = c*dado[k+j+n1].real - s*dado[k+j+n1].imag;
                      t2 = s*dado[k+j+n1].real + c*dado[k+j+n1].imag;
                      dado[k+j+n1].real = dado[k+j].real - t1;
                      dado[k+j+n1].imag = dado[k+j].imag - t2;
                      dado[k+j].real += t1;
                      dado[k+j].imag += t2;
                }
          }
    }
}

/* Função que cálcula a DFT e sua inversa. Se inverse = 0, calcuala a DFT
Se inverse = 1, calcula a IDFT */
void init_sincos_table(double sin_table[DATASIZE][DATASIZE], double cos_table[DATASIZE][DATASIZE], int N){
	unsigned int m, n;
	double theta, cos_theta, sin_theta;
	 double f = 1.0/N;
	 printf("initialising tables..\n");
	for(m = 0; m < N; m++){
	         for(n = 0; n < N; n++){
	             theta = 2*M_PI*m*n*f;
	             cos_theta = cos(theta);
	             sin_theta = sin(theta);
	             cos_table[m][n] = cos_theta;
	             sin_table[m][n] = sin_theta;
	         }
	 }
}

void dft(COMPLEXO in_data[DATASIZE], COMPLEXO out_data[DATASIZE], unsigned int inverse, unsigned int N)
{
     unsigned int m, n;
     double pi2 = (inverse)? 2.0*M_PI : -2.0*M_PI;
     double theta, cos_theta, sin_theta;
     double f = 1.0/N;

    // imprime(&in_data[0], N, "Dados em processamento");
     for(m = 0; m < N; m++){
         out_data[m].real = 0;
         out_data[m].imag = 0;
         for(n = 0; n < N; n++){
             theta = pi2*m*n*f;
             cos_theta = cos(theta);
             sin_theta = sin(theta);
             out_data[m].real += in_data[n].real*cos_theta + in_data[n].imag*sin_theta;
             out_data[m].imag += (-1)*in_data[n].real*sin_theta + in_data[n].imag*cos_theta;
             // printf("\nOut.real = %f\nOut.imag = %f\n", out_data[m].real, out_data[m].imag);
         }
         if(!inverse){
             out_data[m].real *= f;
             out_data[m].imag *= f;
         }
        // printf("Interacao m = %d\n", m);
        // imprime(&out_data[0], N, "Dados em processamento");
     }
}

void dft_tabled(COMPLEXO in_data[DATASIZE], COMPLEXO out_data[DATASIZE], unsigned int inverse, unsigned int N, double sin_table [DATASIZE][DATASIZE], double cos_table[DATASIZE][DATASIZE])
{
     unsigned int m, n;
     double pi2 = (inverse)? 2.0*M_PI : -2.0*M_PI;
     double theta, cos_theta, sin_theta;
     double f = 1.0/N;

    // imprime(&in_data[0], N, "Dados em processamento");
     for(m = 0; m < N; m++){
         out_data[m].real = 0;
         out_data[m].imag = 0;
         for(n = 0; n < N; n++){
             out_data[m].real += in_data[n].real*cos_table[m][n] + in_data[n].imag*sin_table[m][n];
             out_data[m].imag += (-1)*in_data[n].real*sin_table[m][n] + in_data[n].imag*cos_table[m][n];
             // printf("\nOut.real = %f\nOut.imag = %f\n", out_data[m].real, out_data[m].imag);
         }
         if(!inverse){
             out_data[m].real *= f;
             out_data[m].imag *= f;
         }
        // printf("Interacao m = %d\n", m);
        // imprime(&out_data[0], N, "Dados em processamento");
     }
}

/*IMPRIME: Função que imprime como uma tabela todos os pontos de um vetor COMPLEXO*/
void imprime(COMPLEXO * d, int size, char * titulo){
     int s = size;
     float abs = 0;
     printf("\t%s\n", titulo);
     printf(" ___________________________________ \n");
     printf("|Real       |Imaginario | Absolute  |\n");
     printf("+-----------+-----------+-----------+\n");
     while(s-- > 0){
                  if(d){
                     abs = sqrt( pow(d->real,2) + pow(d->imag , 2) );
                     printf("|% 5.5f   | % 5.5f i| % 5.5f  |\n", d->real, d->imag, abs);
                     d++;
                  }
     }
     printf(" ___________________________________ \n\n");
}

float soma_real_imag(COMPLEXO * dados){
	float s;
	s = sqrtf( dados->real*dados->real + dados->imag*dados->imag );
	return s;
}
void copy_data_to_complex(short * data, int size, COMPLEXO * dados){
	while(size-- > 0){
		if(data){//Verifica se o ponteiro é valido
			dados->imag = 0;
			dados->real = (float)(*data);
			data++;
			dados++;
		}
	}
}
void copy_complex_to_data(COMPLEXO * dados, int size, short * data){
	float temp;
	while(size-- > 0){
			if(dados){//Verifica se o ponteiro é valido
				temp = soma_real_imag(dados);
				*data = (short)(temp/256);
				data++;
				dados++;
			}
		}
}
void copy_complex_to_complex(COMPLEXO *in, int size, COMPLEXO *out){
	while(size--){
		out->real = in->real;
		out->imag = in->imag;
		in++;
		out++;
	}
}
int reverse_bits(unsigned int i, int n)
{
    int reverse = 0;
    for(; n > 1; n >>= 1){
          reverse = (reverse << 1) | (i & 1);
          i >>= 1;
    }
    return reverse;
}
