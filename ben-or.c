//date : 20210325（ver.1）
//date      : 20160310,20191218,20191220,20191221,20191223,20191224,20191225,20191229,20191230
//auther    : the queer who thinking about cryptographic future
//code name : Ben_Or's irreducibly test for polynomial over GF(2^m)
//code name : OVP - One Variable Polynomial library
//status    : release (ver 1.2) 20211201

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdint.h>
#include <stdbool.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <execinfo.h>
#include <omp.h>
#include <unistd.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/types.h>
#include <assert.h>
#include <pthread.h>
#include <err.h>
#include <errno.h>

//#include "8192.h"
//#include "4096.h"
#include "global.h"
#include "struct.h"
#include "gf.h"

extern int mlt();
extern int mltn();
extern void print_trace();

//データファイルの数（プロセスの数）
#define DAT 5


// unsigned short c[E * K + 1] = {0};

//有限体の元の逆数
unsigned short
oinv(unsigned short a)
{
  int i;

  if (a == 0)
    return -1;

  for (i = 0; i < N; i++)
  {
    if (gf[mlt(fg[a], i)] == 1)
      return (unsigned short)i;
  }

  printf("no return \n");

  return -1;
}

//aに何をかけたらbになるか
unsigned short
equ(unsigned short a, unsigned short b)
{
  int i;

  for (i = 0; i < N; i++)
  {
    if (gf[mlt(fg[a], fg[i])] == b)
      break;
  }
  return i;
}

//OP型からベクトル型への変換
vec o2v(OP f)
{
  vec a = {0};
  int i;

  for (i = 0; i < DEG; i++)
  {
    if (f.t[i].a > 0 && f.t[i].n < DEG)
      a.x[f.t[i].n] = f.t[i].a;
  }

  return a;
}

//ベクトル型からOP型への変換
OP v2o(vec a)
{
  int i, j = 0;
  OP f = {0};

  //#pragma omp parallel for
  for (i = 0; i < DEG; i++)
  {
    if (a.x[i] > 0)
    {
      f.t[j].n = i;
      f.t[j++].a = a.x[i];
    }
  }

  return f;
}

//停止コマンド
void wait2(void)
{
  printf(" (enter number and hit return) "); // 何か表示させたほうが良いだろう
  fflush(stdout);                            // just in case
  getchar();
}

//OP型を正規化する
OP conv(OP f)
{
  return v2o(o2v(f));
}

//項の数
int terms(OP f)
{
  int i, count = 0;

  for (i = 0; i < DEG; i++)
  {
    if (f.t[i].a > 0)
      count++;
  }

  return count;
}

//多項式の次数(default)
int deg(vec a)
{
  int i, n = 0, flg = 0;

  //#pragma omp parallel for
  for (i = 0; i < DEG; i++)
  {
    if (a.x[i] > 0)
    {
      n = i;
      flg = 1;
    }
  }
  if (flg == 0)
    return 0;

  return n;
}

//多項式の次数(degのOP型)
int odeg(OP f)
{
  int i, j = 0;

  for (i = 0; i < DEG; i++)
  {
    if (j < f.t[i].n && f.t[i].a > 0)
      j = f.t[i].n;
  }

  return j;
}

//多項式を表示する（OP型）
void oprintpol(OP f)
{
  int i, n;

  f = conv(f);
  n = odeg(f);
  printf("n=%d\n", n);
  //printf("terms=%d\n", terms(f));
  printf("deg=%d\n", odeg(f));

  for (i = n; i > -1; i--)
  {
    if (f.t[i].a > 0)
      printf("%ux^%u+", f.t[i].a, f.t[i].n);
  }
}

void op_print_raw(const OP f)
{
  puts("op_print_raw:");
  for (int i = 0; i < DEG; i++)
  {
    if (f.t[i].a > 0)
      printf("[%d] %ux^%u\n", i, f.t[i].a, f.t[i].n);
  }
}

bool op_verify(const OP f)
{
  bool end = false;
  unsigned short n_max = 0;
  for (int i = 0; i < DEG; i++)
  {
    if (end && (f.t[i].n != 0 || f.t[i].a != 0))
    {
      op_print_raw(f);
      printf("found data after end: i=%d\n", i);
      print_trace();
      fflush(stdout);
      return false;
    }
    if (f.t[i].a == 0)
    {
      end = true;
      continue;
    }
    if (f.t[i].n + 1 <= n_max)
    {
      op_print_raw(f);
      printf("found invalid order: i=%d\n", i);
      print_trace();
      fflush(stdout);
      return false;
    }
    n_max = f.t[i].n + 1;
  }
  return true;
}

//20200816:正規化したいところだがうまく行かない
//多項式の足し算
OP oadd(OP f, OP g)
{
  //f = conv(f);
  //g = conv(g);
  assert(op_verify(f));
  assert(op_verify(g));

  vec a = {0}, b = {0}, c = {0};
  int i;
  OP h = {0};

  a = o2v(f);
  b = o2v(g);

  for (i = 0; i < DEG; i++)
  {
    c.x[i] = a.x[i] ^ b.x[i];
  }
  h = v2o(c);
  //h=conv(h);
  assert(op_verify(h));
  return h;
}

//リーディングタームを抽出(OP型）
oterm oLT(OP f)
{
  int i, k, j;
  oterm s = {0};

  k = terms(f);
  s = f.t[0];
  for (i = 0; i < k + 1; i++)
  {
    //printf("a=%d %d\n",f.t[i].a,f.t[i].n);
    if (f.t[i].a > 0)
    {
      printf("in LT=%d %d\n", s.a, s.n);
      for (j = i; j < k + 1; j++)
      {
        if (s.n < f.t[j].n)
        {
          s.n = f.t[j].n;
          s.a = f.t[j].a;
        }

      }
    }
  }
  //  exit(1);

  return s;
}

//多項式を項ずつ掛ける
OP oterml(OP f, oterm t)
{
  f = conv(f);
  assert(op_verify(f));
  int i;
  OP h = {0};

  //f=conv(f);
  //k = deg (o2v(f));

  for (i = 0; i < DEG; i++)
  {
    h.t[i].n = f.t[i].n + t.n;
    h.t[i].a = gf[mlt(fg[f.t[i].a], fg[t.a])];
  }

  h = conv(h);
  assert(op_verify(h));
  return h;
}

//多項式の掛け算
OP omul(OP f, OP g)
{
  f = conv(f);
  g = conv(g);
  assert(op_verify(f));
  assert(op_verify(g));
  int i, k, l;
  oterm t = {0};
  OP h = {0}, e = {0};

  k = odeg(f);
  l = odeg(g);
  if (l > k)
  {
    k = l;
  }

  for (i = 0; i < k + 1; i++)
  {
    t = g.t[i];
    e = oterml(f, t);
    h = oadd(h, e);
  }
  assert(op_verify(h));
  return h;
}

//リーディグタームを抽出(default)
oterm LT(OP f)
{
  int i;
  oterm t = {0};

  //k = deg (o2v (f));
  for (i = 0; i < DEG; i++)
  {
    //printf("a=%d %d\n",f.t[i].a,f.t[i].n);
    if (f.t[i].a > 0)
    {
      t.n = f.t[i].n;
      t.a = f.t[i].a;
    }
  }

  return t;
}

//多項式を単行式で割る
oterm LTdiv(OP f, oterm t)
{
  oterm tt = {0}, s = {
                      0};

  tt = LT(f);
  if (tt.n < t.n)
  {
    s.n = 0;
    s.a = 0;
  }
  else if (tt.n == t.n)
  {
    s.n = 0;
    s.a = equ(t.a, tt.a);
  }
  else if (tt.n > t.n)
  {
    s.n = tt.n - t.n;
    s.a = equ(t.a, tt.a);
    //printf("%u\n",s.a);
  }
  else if (t.n == 0 && t.a > 0)
  {
    s.a = gf[mlt(fg[tt.a], oinv(t.a))];
    s.n = tt.n;
  }

  return s;
}

//モニック多項式にする
OP coeff(OP f, unsigned short d)
{
  int i, k;

  f = conv(f);
  k = odeg((f)) + 1;
  for (i = 0; i < k; i++)
    f.t[i].a = gf[mlt(fg[f.t[i].a], oinv(d))];

  return f;
}

//多項式を表示する(default)
void printpol(vec a)
{
  int i, n;

  n = deg(a);

  for (i = n; i > -1; i--)
  {
    if (a.x[i] > 0)
    {
      printf("%u", a.x[i]);
      //if (i > 0)
      printf("x^%d", i);
      //if (i > 0)
      printf("+");
    }
  }
  //  printf("\n");

  return;
}

//多項式の商を取る
OP odiv(OP f, OP g)
{

  f = conv(f);
  g = conv(g);
  assert(op_verify(f));
  assert(op_verify(g));
  int i;
  OP h = {0}, tt = {0};
  oterm b = {0}, c = {0};

  if (LT(f).n == 0 && LT(g).a == 0)
  {
    printf("baka^\n");
    //return f;
    exit(1);
  }
  if (LT(g).a == 0)
  {
    print_trace();
    exit(1);
  }
  if (LT(g).n == 0 && LT(g).a > 1)
    return coeff(f, LT(g).a);

  b = LT(g);
  if (b.a == 1 && b.n == 0)
    return f;
  if (b.a == 0 && b.n == 0)
  {
    printf("baka in odiv\n");
    exit(1);
  }
  if (odeg((f)) < odeg((g)))
  {
    return f;
    //  a=LT(f);
  }

  i = 0;
  while (LT(f).n > 0 && LT(g).n > 0)
  {
    c = LTdiv(f, b);
    assert(c.n < DEG);
    tt.t[i] = c;
    i++;

    h = oterml(g, c);

    f = oadd(f, h);
    if (odeg((f)) == 0 || odeg((g)) == 0)
    {
      //printf ("blake2\n");
      break;
    }

    if (c.n == 0)
      break;
  }

  // tt は逆順に入ってるので入れ替える
  OP ret = {0};
  int tt_terms = terms(tt);
  for (i = 0; i < tt_terms; i++)
  {
    ret.t[i] = tt.t[tt_terms - i - 1];
  }
  ret = conv(ret);
  assert(op_verify(ret));
  return ret;
}

//多項式のべき乗
OP opow(OP f, int n)
{
  int i;
  OP g = {0};

  g = f;

  for (i = 1; i < n; i++)
    g = omul(g, f);

  return g;
}

//多項式の剰余を取る
OP omod(OP f, OP g)
{
  OP h = {0};
  oterm b = {0}, c = {0};

  if (LT(f).n < LT(g).n)
  {
    //    exit(1);
    return f;
  }

  b = LT(g);

  while (LT(f).n > 0 && LT(g).n > 0)
  {

    c = LTdiv(f, b);
    h = oterml(g, c);
    f = oadd(f, h);
    if (odeg((f)) == 0 || odeg((g)) == 0)
    {
      break;
    }

    if (c.n == 0 || b.n == 0)
      break;
  }

  return f;
}

//

void table(OP x, OP mod,OP *tbl)
{
  int i;
 

  tbl[0] = x;
  for (i = 0; i < K / 2; i++)
  {
    tbl[i + 1] = omod(omul(tbl[i], tbl[i]), mod);
    //printpol(o2v(tbl[i+1]));
    //printf(" =====tbl\n");
  }
  //exit(1);
}

OP opwm(OP f, OP mod, int n)
{
 OP tbl[K / 2 + 1] = {0};

  table(f, mod,tbl);

  return tbl[n];
}

//多項式のべき乗余
OP opowmod(OP f, OP mod, int n)
{
  int i;
  OP t[K / 2] = {0};
  t[0] = f;

  //繰り返し２乗法
  for (i = 1; i < n + 1; i++)
    t[0] = omod(omul(t[0], t[0]), mod);

  return t[0];
}

unsigned short
v2a(oterm a)
{
  int j;

  if (a.a == 0)
    return 0;

  //printf("aa=%d\n",a.a);
  for (j = 0; j < N; j++)
  {
    if (gf[j] == a.a && a.a > 0)
    {
      //printf("j==%d\n",j);
      return j - 1;
    }
  }

  printf("baka-v2a\n");
  exit(1);
}

void printsage(vec a, FILE *fp)
{
  int i, j;
  oterm b;

  //  fp=fopen("dat","w");
  fprintf(fp, "poly=");
  for (i = 0; i < DEG; i++)
  {
    if (a.x[i] > 0)
    {
      b.a = a.x[i];
      b.n = i;
      j = v2a(b);
      //printf("%d,==ba\n",b.a);
      //printf ("X**%d+", i); //for GF2
      if (i == K)
      {
        fprintf(fp, "B('a^%d')*X**%d;", j, i); //for GF(2^m)
      }
      else
      {
        fprintf(fp, "B('a^%d')*X**%d+", j, i); //for GF(2^m)
      }
    }
  }
}

//gcd
OP gcd(OP xx, OP yy)
{
  OP tt = {0}, tmp, h = {0};

  h.t[0].a = 1;
  h.t[0].n = 0;
  if (deg(o2v(xx)) < deg(o2v(yy)))
  {
    tmp = xx;
    xx = yy;
    yy = tmp;
  }
  tt = omod(xx, yy);
  while (odeg(tt) > 0)
  {
    xx = yy;
    yy = tt;
    if (odeg(yy) > 0)
      tt = omod(xx, yy);
    if (LT(tt).a == 0)
      return yy;
  }
  if (LT(tt).a == 0)
  {
    return yy;
  }
  else
  {
    return h;
  }
  //  return yy;
}

//０多項式かどうかのチェック
unsigned char
chk(OP f)
{
  int i, flg = 0;
  vec x = {0};

  x = o2v(f);
  for (i = 0; i < DEG; i++)
  {
    if (x.x[i] > 0)
    {
      flg = 1;
      return 1;
    }
  }
  if (flg == 0)
    return 0;

  exit(1);
}

OP init_pol(OP f)
{
  int i;

  for (i = 0; i < DEG; i++)
  {
    f.t[i].a = 0;
    f.t[i].n = 0;
  }

  return f;
}

//ランダム多項式の生成
 void
ginit(unsigned short *g)
{
  int j, count = 0, k = 0;
  unsigned short gg[K + 1] = {0};

  //printf("in ginit\n");

  g[K] = 1;          //xor128();
  g[0] = rand() % N; //or N
  k = rand() % (K - 1);
  if (k > 0)
  {
    while (count < k)
    {
      //printf("in whule\n");
      j = rand() % (K);
      if (j < K && j > 0 && g[j] == 0)
      {
        g[j] = rand() % N; //or N;
        count++;
      }
    }
  }

  for (j = 0; j < K + 1; j++)
    gg[j] = g[K - j];

  memcpy(g, gg, sizeof(K + 1));
}

//整数からベクトル型への変換
vec i2v(unsigned short n)
{
  vec v = {0};
  int i = 0;

  while (n > 0)
  {
    v.x[i++] = n % 2;
    n = (n >> 1);
  }

  return v;
}

//ベクトル型から整数への変換
unsigned short
v2i(vec v)
{
  unsigned int d = 0, i, e = 0;

  for (i = 0; i < deg(v) + 1; i++)
  {
    e = v.x[i];
    d ^= (e << i);
  }

  return d;
}



//整数のべき乗
unsigned int
ipow(unsigned int q, unsigned int u)
{
  unsigned int i, m = 1;

  for (i = 0; i < u; i++)
    m *= q;

  printf("in ipow====%d\n", m);

  return m;
}



//配列からベクトル表現の多項式へ変換する
//配列の値を係数として多項式に設定する
OP setpol(unsigned short f[], int n)
{
  OP g;
  vec c={0};  //[E * K + 1] = {0};
  int i;
  vec v = {0};

  memset(c.x, 0, sizeof(c));
  memcpy(c.x, f, 2 * n);


  for (i = 0; i < n; i++)
  {
    v.x[n - 1 - i] = c.x[i];
  }

  g = v2o(v);

  return g;
}

OP mkpol()
{
  int i, j, k, flg, ii = 0;
  OP w = {0};
   unsigned short g[K + 1] = {0};

  do
  {
    j = 0;
    k = 0;
    flg = 0;

    memset(g, 0, sizeof(g));
    //memset(ta, 0, sizeof(ta));
    memset(w.t, 0, sizeof(w));
    ginit(g);
    ii++;
    if (ii > K / 2)
    {
      printf("erro=%d\n", ii);
      exit(1);
    }

    for (i = 0; i < K; i++)
    {
      if (g[K - 1] > 0)
        flg = 1;
      if (i % 2 == 1 && g[i] > 0 && i < K)
        k++;
    }

    //偶数項だけにならないようにする
    if ((k > 0 && flg == 0) || (k > 1 && flg == 1))
    //if(k>0)
    {
      w = setpol(g, K + 1);
      j = 1;
      //if(isquad(w)==-1)
      //exit(1);
    }
    // exit(1);

  } while (j == 0);

  //printpol(o2v(w));
  //printf(" ==g\n");
  //exit(1);

  return w;
}

//GF(2^m) then set m in this function.
int ben_or(OP f)
{
  int i, n; //, pid;
  OP s = {0}, u = {0}, r = {0};
  vec v = {0};
  //if GF(8192) is 2^m and m==13 or if GF(4096) and m==12 if GF(16384) is testing
  //int m = E;
  // m=12 as a for GF(4096)=2^12 defined @ gloal.h or here,for example m=4 and GF(16)

  v.x[1] = 1;
  s = v2o(v);
  //for (i = 0; i < K / 2; i++)
  r = s;
  n = deg(o2v(f));

  if (LT(f).n == 0 && LT(f).a == 1)
  {
    printf("f==0\n");
    exit(1);
  }
  if (n == 0)
    return -1;

  i = 0;

  //r(x)^{q^i} square pow mod
  for (i = 0; i < K / 2; i++)
  {
    // irreducible over GH(8192) 2^13
    r = opowmod(r, f, E);
    u = oadd(r, s);
    u = gcd(f, u);

    if (odeg(u) > 0)
    {
      //flg[i]= -1;
      return -1;
    }
  }

  return 0;
}

//多項式の代入値
unsigned short
trace(OP f, unsigned short x)
{
  int i, d;
  unsigned short u = 0;

  d = deg(o2v(f));

  for (i = 0; i < d + 1; i++)
  {
    u ^= gf[mlt(fg[f.t[i].a], mltn(f.t[i].n, fg[x]))];
  }

  return u;
}



void get_irrpoly(void)
{
  int i, j, l, ii = 0;
  OP w = {0};
  FILE *fp;
  unsigned short ta[N] = {0};

  j = 0;
  fp = fopen("dat.sage", "w");

while(1){

  //printf("\n");

  //既約性判定のためのBen-Orアルゴリズム。拡大体にも対応している。デフォルトでGF(8192)
  l = -1;
  ii = 0;

  while (l == -1)
  {
    w = mkpol();
    l = ben_or(w);
    printf("irr=%d\n", l);
    if (ii > 300)
    {
      printf("too many tryal\n");
      exit(1);
    }
    printf("ben=%d\n", ii);
    ii++;
    //
  }

  //多項式の値が0でないことを確認
  for (i = 0; i < N; i++)
  {
    ta[i] = trace(w, i);
    if (ta[i] == 0)
    {
      printf("trace 0 @ %d\n", i);
      //fail = 1;
      exit(1);
    }
  }

  printpol(o2v(w));
  printf(" =irreducible\n");
  printsage(o2v(w), fp);
  fprintf(fp, " print(poly.is_irreducible());\n");
  j++;

  if (j > 10)
  {
    fclose(fp);
    exit(1);
  }
}

}

//sagemath仕様の既多項式をファイルに書き出す（マルチプロセス）
int irr_poly_to_file()
{
  OP w, x, y, z;
  int b = -1, l = -1, k1 = 0, k2 = 0, k3 = 0, k4 = 0, a = -1, c = -1, i = 0;
  FILE *f1, *f2, *f3, *f4;
  int pid[5] = {0};

  for (i = 0; i < 3 && (pid[i] = fork()) > 0; i++)
    printf("%d\n", pid[i]);
  //exit(1);
  f1 = fopen("dat.sage", "w");
  f2 = fopen("dat0.sage", "w");
  f3 = fopen("dat1.sage", "w");
  f4 = fopen("dat2.sage", "w");
  //f5=fopen("dat3.sage","w");
  //this is child process
  fprintf(f1, "B=GF(2^%d,'a')\n", E);
  fprintf(f1, "F.<X>=B[]\n");
  fprintf(f2, "B=GF(2^%d,'a')\n", E);
  fprintf(f2, "F.<X>=B[]\n");
  fprintf(f3, "B=GF(2^%d,'a')\n", E);
  fprintf(f3, "F.<X>=B[]\n");
  fprintf(f4, "B=GF(2^%d,'a')\n", E);
  fprintf(f4, "F.<X>=B[]\n");

  i = 0;
  while (1)
  {

    l = -1;
    w = mkpol();
    b = -1;
    x = mkpol();
    a = -1;
    y = mkpol();
    c = -1;
    z = mkpol();

    if (pid[2] > 0)
    {
      l = ben_or(w);
      if (l == 0 && k1 < DAT)
      {
        printsage(o2v(w), f1);
        fprintf(f1, " print(poly.is_irreducible());\n");
        l = -1;
        k1++;
        printf("k1=%d\n", k1);
        if (k1 == DAT)
        {
          fclose(f1);
          wait(&pid[0]);
          wait(&pid[1]);
          wait(&pid[2]);
          exit(1);
        }
        //goto aa;
      }
    }
    else if (pid[1] > 0)
    {
      // }//this is mother process

      b = ben_or(x);
      if (b == 0 && k2 < DAT)
      {
        printsage(o2v(x), f2);
        fprintf(f2, " print(poly.is_irreducible());\n");
        b = -1;
        k2++;
        printf("k2=%d\n", k2);

        if (k2 == DAT)
        {
          fclose(f2);
          _exit(0);
          //wait(&pid[1]);
        }
        //goto aa;
      }
    }
    //}//this is mother process

    else if (pid[0] > 0)
    {

      //if(pid[1] == 0){
      a = ben_or(y);
      if (a == 0 && k3 < DAT)
      {
        printsage(o2v(y), f3);
        fprintf(f3, " print(poly.is_irreducible());\n");
        a = -1;
        k3++;
        printf("k3=%d\n", k3);

        if (k3 == DAT)
        {
          fclose(f3);
          _exit(0);
          //wait(&pid[0]);
        }
        //goto aa;
      }
    }
    else if (pid[0] == 0)
    {
      //this is mother process

      c = ben_or(z);
      if (c == 0 && k4 < DAT)
      {
        printsage(o2v(z), f4);
        fprintf(f4, " print(poly.is_irreducible());\n");
        c = -1;
        k4++;
        printf("k4=%d\n", k4);
        if (k4 == DAT)
        {
          fclose(f4);
          _exit(0);
        }
        //goto aa;
      }
    }
  }

  return 0;
}

//言わずもがな
int main(void)
{
  unsigned short f[K + 1] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 0}; //big indian
  OP g;
  int i;

  //test , usage and example
  for (i = 0; i < N; i++)
  {
    memset(&g ,0,sizeof(g));
    f[K] = i;
    g = setpol(f, K + 1);
    if (ben_or(g) == 0)
    {
      printpol(o2v(g));
      printf(" is irreducible\n");
    }
    else
    {
      printf("reducible\n");
    }
  }

  //multi_process();
  //irr_poly_to_file();
  //get_irrpoly();

  return 0;
}
