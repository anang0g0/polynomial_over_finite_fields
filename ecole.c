/* generate GF(2^n) using irreducible polynomial */
// ゼフ対数表を作るためのプログラム。正規基底を生成します。

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ORD 65536

static unsigned short gf[ORD] = {0}, fg[ORD] = {0};

void ens(unsigned int x, int n, char *argv[])
{
  int i, j, k = x, count = 0, ord = atoi(argv[1]);
  FILE *fp;
  char c[] = ".h";

  strcat(argv[1], c);
  fp = fopen(argv[1], "wb");

  while (k > 0)
  {
    k = (k >> 1);
    count++;
  }
  fprintf(fp, "static const unsigned short gf[%d]={\n", ord);
  k = (1 << (count - 1));
  gf[0] = 0;
  gf[1] = 1;
  gf[2] = 2;
  for (i = 3; i < n; i++)
  {
    gf[i] = (gf[i - 1] << 1);
  }
  // exit(1);
  if (n < 3)
    n = 2;
  for (i = n; i < ord; i++)
  {
    if (gf[i] < k)
      gf[i] = (gf[i - 1] << 1);
    if (gf[i] >= k)
      gf[i] ^= x;
    //  printf("%d,",gf[i]);
  }
  for (i = 0; i < ord; i++)
  {
    if (i < ord - 1)
    {
      fprintf(fp,"%d,",gf[i]);
    }
    if (i == ord - 1)
    {
      fprintf(fp,"%d",gf[i]);
    }
  }
  fprintf(fp, "};\n");

  for (i = 0; i < ord; i++)
  {
    for (j = 0; j < ord; j++)
    {
      if (gf[i] == j)
        fg[j] = i;
    }
  }
  fprintf(fp, "static const unsigned short fg[%d]={", ord);
  for (i = 0; i < ord; i++)
  {
    if (i < ord - 1)
    {
      fprintf(fp,"%d,",fg[i]);
    }
    else
    {
      fprintf(fp,"%d",fg[i]);
    }
  }
  fprintf(fp, "};\n");
}

int main(int argc, char *argv[])
{
  int k;
  int x, n = 0;
  /* Generate nomal basis of Galois Field over GF(2^?) */
  static const unsigned int normal[14] = {
      0b1101,
      0b11001,
      0b110111,
      0b1100001,
      0b11000001,
      0b110101001,
      0b1100110001,
      0b11000010011,
      0b110000001101,
      0b1100101000001,
      0b11011000000001,
      0b110000100010001,
      0b1100000000000001,
      0b11010000000010001};

  // Generate Sagemath based Galois Fields.
  static const unsigned int sage[14] = {
      0b1011,
      0b10011,
      0b100101,
      0b1011011,
      0b10000011,
      0b100011101,      // sage
      0b1000010001,     // sage512
      0b10001101111,    // sage1024
      0b100000000101,   // 2048
      0b1000011101011,  /* sage 4096 */
      0b10000000011011, /* Classic McEliece */
      0b100000010101001,
      0b1000000000110101,
      0b10000000000101101};

  if (argv[1] == NULL)
  {
    printf("Please input with order of finite fields.\n");
    exit(1);
  }
  k = atoi(argv[1]);
  if(i<8){
    printf("Please input more  GF(8).\n")
  }

  while (k > 0)
  { 
    if(k%2==1 && k>1){
    printf("This number is not 2^m.\n");
    exit(1);
    }
    k = (k >> 1);
    n++;
  }
  if (n == 0)
  {
    printf("baka\n");
    exit(1);
  }

  x = normal[n - 4];

  ens(x, n - 4, argv);

  return 0;
}
