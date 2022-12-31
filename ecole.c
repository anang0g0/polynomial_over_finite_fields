/************************************************************
 * ecole.c - generate GF(2^n) using irreducible polynomial
 *  ゼフ対数表を作るプログラム。正規基底を生成します。
 *  GF : Galois Field
 * Author: Osamu Sakai, SCI(SAKAI Cryptography Institute)
 *
 *  Edition History
 * version date       comment                                     by
 * ------- ---------- ------------------------------------------- ---------
 * V0.5    2022/12/01 beta version                                O.Sakai
 * V0.6    2022/12/10 refactoring                                 rubato6809
 * V0.61   2022/12/20 changed not to support order=65536          O.Sakai
 * V0.8    2023/12/30 remove a order 65536                        O.Sakai
 *
 * Copyright(c) 2022 - 2023 SCI, All Rights Reserved
 */

#include <stdio.h>
#include <stdlib.h>

#define MAX_ORD 32768

/***************************************************************
 * 関数名     : void gen_gf(int deg, int order)
 * 機能       : 引数 deg をもつ原始多項式を使って、order 個の有限体を生成する。
 *              許容する order の範囲は 4(=2^2) から 32768(=2^15) まで.
 *              許容しない値なら、使用法を表示し、exit(1) する.
 *
 * 入力引数   : int deg, int order
 * 出力引数   : none
 * 戻り値     : 2 ～ 15
 *              エラー（許容しない値）の場合、戻り値無し。プロセス終了
 * 入力情報   : none
 * 出力情報   : none
 * 注意事項   :     num         | return value
 *              ----------------+-------------
 *                    2 = 2^1   |   exit(1)
 *                    4 = 2^2   |         2
 *                    8 = 2^3   |         3
 *                    :         |         :
 *                32768 = 2^15  |        15
 *                65536 = 2^16  |   exit(1)
 ****************************************************************/
// Zech対数の正引き gf と逆引き fg
static unsigned short gf[MAX_ORD];
static unsigned short fg[MAX_ORD];
void gen_gf(int exp, int order)
{
    /* Generate nomal basis of Galois Field over GF(2^?) */
    static const unsigned int normal[] = {
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
    };

    // Generate Sagemath based Galois Fields.
    static const unsigned int sage[] = {
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
    };

    unsigned short x = normal[exp - 2];

    /* build gf[] */
    gf[0] = 0;
    gf[1] = 1;
    /*
    for (int i = 2; i < order; i++)
    {
        gf[i] = (gf[i - 1] << 1); // gf[i] を更新する
        if (gf[i] >= order)       // gf[i] 検査
            gf[i] ^= x;
    }
    */

    unsigned short value = 1;
    for (int i = 2; i < order; i++)
    {
        value <<= 1;
        if (value >= order)
            value ^= x;

        gf[i] = value;
    }
    /* build fg[] */
    for (int i = 0; i < order; i++)
        fg[gf[i]] = i;
}

void toFile(FILE *fp, int order, unsigned short *array, char *name)
{
    fprintf(fp, "static const unsigned short %s[%d]={", name, order);
    for (int i = 0; i < order; i++)
        fprintf(fp, "%d,", array[i]);
    fprintf(fp, "};\n");
}

void put_gf(int order)
{
    char filename[8];
    sprintf(filename, "%d.h", order);
    FILE *fp = fopen(filename, "wb");

    toFile(fp, order, gf, "gf");
    toFile(fp, order, fg, "fg");

    fclose(fp);
}

void usage(void)
{
    printf("Please input order of finite fields.\n");
    exit(1);
}

/***************************************************************
 * 関数名     : int bitsize(int num)
 * 機能       : 引数 num が 2 のべき乗数ならば、べき数 exponent を返す.
 *              許容する num の範囲は 4(=2^2) から 32768(=2^15) まで.
 *              許容しない値なら、使用法を表示し、exit(1) する.
 *
 * 入力引数   : int num
 * 出力引数   : none
 * 戻り値     : 2 ～ 15
 *              エラー（許容しない値）の場合、戻り値無し。プロセス終了
 * 入力情報   : none
 * 出力情報   : none
 * 注意事項   :     num         | return value
 *              ----------------+-------------
 *                    2 = 2^1   |   exit(1)
 *                    4 = 2^2   |         2
 *                    8 = 2^3   |         3
 *                    :         |         :
 *                32768 = 2^15  |        15
 *                65536 = 2^16  |   exit(1)
 ****************************************************************/
int bitsize(int num)
{
    int power2 = 4;
    for (int nbits = 2; nbits < 16; nbits++)
    {
        if (num == power2)
            return nbits; // 当り。ビット数を返す

        power2 <<= 1; // 4, 8, 16 ... 65536
    }
    /* ここまできたらハズレ */
    usage();      // 使用方法を表示して（exit() しちゃう？）
    return 0; // 負の値を返してエラーってことで
}

int main(int argc, char *argv[])
{
    if (argc == 1)
        usage();

    int k = atoi(argv[1]);
    int n = bitsize(k);
    printf("n=%d\n",n);

    gen_gf(n, k);
    put_gf(k);

    return 0;
}
