/* generate GF(2^n) using irreducible polynomial */
// ゼフ対数表を作るためのプログラム。正規基底を生成します。

#include <stdio.h>
#include <stdlib.h>

#define ORD 32

void ens(unsigned int x, int n)
{
  int i, j, k = x, count = 0;
  unsigned int gf[ORD] = {0}, fg[ORD] = {0};

  while (k > 0)
  {
    k = (k >> 1);
    count++;
  }
  printf("static const unsigned short gf[%d]={\n", ORD);
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
  for (i = n; i < ORD; i++)
  {
    if (gf[i] < k)
      gf[i] = (gf[i - 1] << 1);
    if (gf[i] >= k)
      gf[i] ^= x;
    //  printf("%d,",gf[i]);
  }
  for (i = 0; i < ORD; i++)
  {
    if (i < ORD - 1)
      printf("%d,", gf[i]);
    if (i == ORD - 1)
      printf("%d", gf[i]);
  }
  printf("};\n");

  for (i = 0; i < ORD; i++)
  {
    for (j = 0; j < ORD; j++)
    {
      if (gf[i] == j)
        fg[j] = i;
    }
  }
  printf("static const unsigned short fg[%d]={", ORD);
  for (i = 0; i < ORD; i++)
  {
    if (i < ORD - 1)
    {
      printf("%d,", fg[i]);
    }
    else
    {
      printf("%d", fg[i]);
    }
  }
  printf("};\n");
}

int main()
{
  int k = ORD;
  int x, n = 0;
  /* generate Galois Field over GF(2^?) */
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

  while (k > 0)
  {
    k = (k >> 1);
    n++;
  }
  printf("n=%d %d noemal[%d]\n", n, n - 4, normal[n - 4]);
  // exit(1);
  x = normal[n - 4];

  ens(x, n - 4);

  return 0;
}
