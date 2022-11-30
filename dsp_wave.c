#include <stdio.h>
#include <math.h>
#include "dsp_util.h"
#include "dsp_wave.h"

unsigned int dsp_convert_to_twos_complement(double y, int dac_resol_bits)
{
 double vref_p=1.0, vref_n=-1.0, amplitude=1.0;
 int pos_scale = (1 << (dac_resol_bits-1))-1;
 int neg_scale = 1 << (dac_resol_bits-1);
 if (vref_n < 0) vref_n = -vref_n;
 int N = dac_resol_bits;
 char a[N_DSP_VEC_MAX], result[N_DSP_VEC_MAX], one_vec[N_DSP_VEC_MAX], tmp[N_DSP_VEC_MAX];
 int data, res;

 if (y >= 0) {
  y = pos_scale*(y/vref_p);
  res = y;
 }
 else {
  y = -y;
  y = neg_scale*(y/vref_n);
  data = y;

  dsp_store_num(a, data, N);
  dsp_store_num(one_vec, 1, N);
  dsp_notvec(a, tmp,  N);
  dsp_unsigned_add(tmp, one_vec, result, N);
  res = dsp_todec(result, N);
 }

 return res;
}

// c: signal code (sine, ...)
// T: period in sec-s
// N: number of samples per period
void dsp_create_wave(int c, double T, int N, int dac_resol_bits)
{
 double t, y;
 unsigned int d;

 for (int i=0; i<N; i++) {
  t = T/N*i;

  if (c == SIG_SINE)
   y = sin(2*M_PI/T*t);
  else if (c == SIG_SQUARE) {
   if (t <= T/2) y = 1; else y = -1;
  }
  else if (c == SIG_SAW) {
   y = t;
  }

  d = dsp_convert_to_twos_complement(y, dac_resol_bits);

  #ifdef DEBUG
  printf("x: %f, y: %f, d: 0x%04x\n", t, y, d);
  #endif
 }

 // Testing max min values
 #ifdef DEBUG
 d = dsp_convert_to_twos_complement(1, dac_resol_bits);
 printf("1: d: 0x%04x\n", d);

 d = dsp_convert_to_twos_complement(-1, dac_resol_bits);
 printf("-1: d: 0x%04x\n", d);
 #endif

}

