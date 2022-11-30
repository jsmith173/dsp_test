#include <stdio.h>
#include "dsp_util.h"
#include "dsp_wave.h"

int main(void)
{
 char a[N_DSP_VEC_MAX], b[N_DSP_VEC_MAX], s1[N_DSP_VEC_MAX], result[N_DSP_VEC_MAX];
 int res, N=8;

 printf("\n");

 dsp_store_num(a, 0xC8, N); dsp_tobin(a, N, s1); printf("s1: %s\n", s1);
 dsp_store_num(b, 0x3C, N); dsp_tobin(b, N, s1); printf("s2: %s\n", s1);
 dsp_unsigned_add(a, b, result, N); dsp_tobin(result, N, s1); res = dsp_todec(result, N);
 if (res != 0x04) printf("Error\n"); else printf("OK\n");

 dsp_create_wave(SIG_SINE, 1, 100, 16);

 return 0;
}



