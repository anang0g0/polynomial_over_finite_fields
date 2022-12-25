/* generate GF(2^n) using irreducible polynomial */
// ゼフ対数表を作るためのプログラム。正規基底を生成します。

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ORD 65536

static unsigned short gf[ORD] = {0}, fg[ORD] = {0};

// Generate Zech logarithm
void gen_GF(int n, int order)
{

    /* Generate nomal basis of Galois Field over GF(2^?) */
    static const unsigned int normal[15] = {
        0b111,
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

/*
    // Generate Sagemath based Galois Fields.
    static const unsigned int sage[15] = {
        0b111,
        0b1011,
        0b10011,
        0b100101,
        0b1011011,
        0b10000011,
        0b100011101,      // sage
        0b1000010001,     // sage512
        0b10001101111,    // sage1024
        0b100000000101,   // 2048
        0b1000011101011,  // sage 4096 
        0b10000000011011, // Classic McEliece 
        0b100000010101001,
        0b1000000000110101,
        0b10000000000101101};
*/
    int k, x;
    x = k = normal[n];

    gf[0] = 0;
    gf[1] = 1;
    
    int i;
    for (i = 2; i < order; i++)
    {
        if (gf[i] < k)
            gf[i] = (gf[i - 1] << 1);
        if (gf[i] >= k)
            gf[i] ^= x;
    }
    for (i = 0; i < order; i++)
    {
        for (int j = 0; j < order; j++)
        {
            if (gf[i] == j)
                fg[j] = i;
        }
    }
}

// Write Zech logarithm
void put_GF(int order)
{
    FILE *fp;
    char filename[8] = "";

    sprintf(filename, "%d.h", order);
    fp = fopen(filename, "wb");

    int lastone = order - 1;
    int i;
    fprintf(fp, "static const unsigned short gf[%d]={\n", order);
    for (i = 0; i < lastone; i++)
        fprintf(fp, "%d,", gf[i]);
    fprintf(fp, "%d};\n", gf[lastone]);

    fprintf(fp, "static const unsigned short fg[%d]={", order);
    for (i = 0; i < lastone; i++)
        fprintf(fp, "%d,", fg[i]);
    fprintf(fp, "%d};\n", fg[lastone]);
    fclose(fp);
}

int valid(int k)
{
    int n = 0;

    if (k < 4)
        printf("Please input more  GF(4).\n");

    while (k > 0)
    {
        if (k % 2 == 1 && k > 1)
        {
            printf("This number is not 2^m.\n");
            exit(1);
        }
        k = (k >> 1);
        n++;
    }

    return n;
}

int main(int argc, char *argv[])
{

    if (argv[1] == NULL)
    {
        printf("Please input order of finite fields.\n");
        exit(1);
    }

    int k;
    int n = 0;
    k = atoi(argv[1]);
    n = valid(k);

    gen_GF(n - 3, k);
    put_GF(k);
    return 0;
}
