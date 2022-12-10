/* generate GF(2^n) using irreducible polynomial */
//ゼフ対数表を作るためのプログラム。正規基底を生成します。

#include <stdio.h>
#include <stdlib.h>

#define O 8192

/* generate Galois Field over GF(2^?) */
static const unsigned long long int normal[15] = {
    0b1011,
    0b10011,
    0b110111,
    0b1100001,
    0b11000001,
    0b100011101, // sage
    0b1000010001, //sage512
    0b10001101111, // sage1024
    0b100000000101, //2048
    0b1000011101011, // sage 4096
    //0b1000000001001,
    //0b11011000000001, /* 8192 */
    0b10000000011011, /* Classic McEliece */
    0b110000100010001,
    0b1100000000000001,
    0b11010000000010001};

unsigned int gf[O], fg[O];

void makefg(int n)
{
  int i, j;

  for (i = 0; i < n; i++)
  {
    for (j = 0; j < n; j++)
    {
      if (gf[i] == j)
        fg[j] = i;
    }
  }
  printf("static const unsigned short fg[%d]={", O);
  for (i = 0; i < O; i++)
  {
    if (i < O - 1)
    {
      printf("%d,", fg[i]);
    }
    else
    {
      printf("%d", fg[i]);
    }
  }
  printf("};\n");

  return;
}

void mkgf(int n)
{
  int i, j, bit, count = 0;
  unsigned int pol, N, M, L;

  for (i = 0; i < 13; i++)
    pol = normal[i]; // strtoul(normal[i],(char **)NULL,2);

  /* define pol */
  switch (n)
  {

  case 8:
    pol = normal[0];
    printf("%d\n", n);
    break;

  case 16:
    pol = normal[1];
    printf("%d\n", n);
    break;

  case 32:
    pol = normal[2];
    printf("%d\n", n);
    break;

  case 64:
    pol = normal[3];
    printf("%d\n", n);
    break;

  case 128:
    pol = normal[4];
    printf("%d\n", n);
    break;

  case 256:
    pol = normal[5];
    printf("%d\n", n);
    break;

  case 512:
    pol = normal[6];
    printf("%d\n", n);
    break;

  case 1024:
    pol = normal[7];
    printf("%d\n", n);
    break;

  case 2048:
    pol = normal[8];
    printf("%d\n", n);
    break;

  case 4096:
    pol = normal[9];
    printf("%d\n", n);
    break;

  case 8192:
    pol = normal[10];
    printf("%d\n", n);
    break;

  default: /* 16384 */
    pol = normal[11];
    printf("%d\n", n);
    break;
  }

  L = 1;
  while (pol > L) //原始多項式の最大次数を計算する。
  {
    L = (L << 1);
    count++;
  }
  L = (L >> 1);
  N = pol ^ L; //原始多項式の最大次数を消した多項式の残り。

  gf[0] = 0;
  bit = 1;
  for (i = 1; i < L; i++)
  {
    if (bit > L - 1) //もしbitが最大次数に達したら
    {
      bit = bit - L; // bitから最大次数の項 x^n を消す。
      bit = bit ^ N; //最大次数の項以下の原始多項式を bit に xorする。
    }
    gf[i] = bit;      //最初は何もしないでx^iを入れていく。
    bit = (bit << 1); //原始多項式の次数を1上げる。
  }
  printf("static const unsigned short gf[%d]={", O);
  for (i = 0; i < L; i++)
  {
    if (i < O - 1)
    {
      printf("%u,", gf[i]);
    }
    else
    {
      printf("%u", gf[i]);
    }
  }

  printf("};\n");
}


void ens(unsigned int x, int n){
unsigned int gf[O]={0};
int i,j,k=x,count=0;

while(k>0){
  k=(k>>1);
  count++;
}
  printf("static const unsigned short gf[%d]={\n",O);
k=(1 << count-1);
gf[0]=0;
gf[1]=1;
gf[2]=2;
for(i=3;i<n;i++){
gf[i]=(gf[i-1]<<1);

}
//exit(1);
for(i=n;i<O;i++){
  if(gf[i]<k)
  gf[i]=(gf[i-1]<<1);
  if(gf[i]>=k)
  gf[i]^=x;
//  printf("%d,",gf[i]);
}
for(i=0;i<O;i++)
printf("%d,",gf[i]);
printf("};\n");

  for (i = 0; i < O; i++)
  {
    for (j = 0; j < O; j++)
    {
      if (gf[i] == j)
        fg[j] = i;
    }
  }
  printf("static const unsigned short fg[%d]={", O);
  for (i = 0; i < O; i++)
  {
    if (i < O - 1)
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
  int i, j, k=O+1;
  int x,n=0,l=1;

while(k>0){
  k=(k>>1);
  n++;
}

printf("%d\n",n);
//exit(1);
//scanf("%d",&n);
x=normal[n-4];
  //x=0b1000000001001,
  //  0b1000011101011; // sage 4096
  
  ens(x,n-4);

//  exit(1);
//  mkgf(O);
//  makefg(O);

  return 0;
}
