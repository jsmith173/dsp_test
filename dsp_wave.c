#include <stdio.h>
#include <math.h>
#include "dsp_wave.h"

unsigned int dsp_convert_to_twos_complement(double y, int dac_resol_bits)
{
 double vref_p=1.0, vref_n=-1.0, amplitude=1.0;
 int pos_scale = (1 << (dac_resol_bits-1))-1;
 int neg_scale = 1 << (dac_resol_bits-1);
 if (vref_n < 0) vref_n = -vref_n;
 int N = dac_resol_bits;
 int data, res, pad;

 if (y >= 0) {
  y = pos_scale*(y/vref_p);
  res = y;
 }
 else {
  y = -y;
  y = neg_scale*(y/vref_n);
  data = y;

  pad = 1 << N;
  pad--;

  data = ~data;
  data &= pad;
  data++;
  
  res = data;
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

