#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//符号のパラーメータの指定。通常[N,K,T]として、
//Nは符号の長さ、Kが符号の次元、Tは訂正エラー数
//を表す。ここではDは符号長にしている。
#define N 16 // 符号長
#define M 16 //有限体の元の数
#define K (128) //符号の次元
#define E (4) //拡大体のビット数
#define DEG 1024 //(K * E) //多項式の次数
#define T (K / 2) //エラーの数


