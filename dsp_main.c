#include <stdio.h>
#include "dsp_wave.h"

int main(void)
{
 int res, N=16;

 printf("\n");

 dsp_create_wave(SIG_SINE, 1, 100, 16);

 return 0;
}



