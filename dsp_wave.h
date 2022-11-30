#ifndef dsp_waveH
#define dsp_waveH

#define SIG_SINE 0
#define SIG_SQUARE 1
#define SIG_SAW 2

void dsp_create_wave(int c, double T, int N, int dac_resol_bits);

#endif
