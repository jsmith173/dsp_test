#include <string.h>
#include "dsp_util.h"

void dsp_inttobinstr(unsigned int val, int len, char* result)
{
 strcpy(result, "");

 for ( int i = 1; i <= len; i++ )
 {
     if ( ( val % 2 ) == 1 ) strcat(result, "1");
     else strcat(result, "0");

     val = val/2;
 }

 strrev(result);
}

void dsp_store_num(char* a, int num, int N)
{
 char s[N_DSP_VEC_MAX];

 dsp_inttobinstr(num, N, s);
 for (int i=0; i<N; i++) {
  if (s[i] == '1')
   a[i] = 1;
  else
   a[i] = 0;
 }
}

// Big endian form: reg [N-1:0] q
void dsp_tobin(char* a, int N, char* result)
{
 strcpy(result, "");
 for (int i=0; i<N; i++) {
  if (a[i] == 1)
   strcat(result, "1");
  else
   strcat(result, "0");
 }
}

// reg [N-1:0] a
unsigned int dsp_todec(char* a, int N)
{
 int val=0;

 for (int i=0; i<N; i++)
  val = 2*val+a[i];
 return val;
}

void dsp_copyvec(char* dest, char* src, int N)
{
 for (int i=0; i<N; i++)
  dest[i] = src[i];
}

void dsp_notvec(char* a, char* result, int N)
{
 for (int i=0; i<N; i++)
  if (a[i]) result[i] = 0; else result[i] = 1;
}

void dsp_unsigned_add(char* a, char* b, char* sum, int N)
{
 int i;
 char temp[N_DSP_VEC_MAX], sum_d[N_DSP_VEC_MAX];
 char carry = 0;

 for (i=N-1; i>=0; i--) {
  sum_d[i] = a[i] ^ b[i] ^ carry;
  carry = (a[i] & b[i]) | (a[i] & carry) | (carry & b[i]);
 }
 dsp_copyvec(sum, sum_d, N);
}


