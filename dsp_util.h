#ifndef dsp_utilH
#define dsp_utilH


#define N_DSP_VEC_MAX 128

typedef char dsp_vec[N_DSP_VEC_MAX];

void dsp_inttobinstr(unsigned int val, int len, char* result);
void dsp_store_num(char* a, int num, int N);
void dsp_notvec(char* a, char* result, int N);
void dsp_tobin(char* a, int N, char* result);
unsigned int dsp_todec(char* a, int N);
void dsp_unsigned_add(char* a, char* b, char* sum, int N);

#endif

