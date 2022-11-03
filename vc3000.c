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
//#include <assert.h>
#include <execinfo.h>
//#include <omp.h>
#include <unistd.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/types.h>

#include "8192.h"
//#include "4096.h"
#include "global.h"
#include "struct.h"
//#include "debug.c"
//#include "chash.c"

#include <pthread.h>
#include <err.h>
#include <errno.h>

extern int mlt();
extern int mltn();
extern void print_trace();

#define DAT 5
int num = 0;

//nomal bases
//unsigned short gf[M]={0,1,2,4,8,9,11,15,7,14,5,10,13,3,6,12};
//unsigned short fg[M]={0,1,2,13,3,10,14,8,4,5,11,6,15,12,9,7};

//sage比較用
//static const unsigned short gf[16]={0,1,2,4,8,3,6,12,11,5,10,7,14,15,13,9};
//static const unsigned short fg[16]={0,1,2,5,3,9,6,11,4,15,10,8,7,14,12,13};

//GF(2^8)
//static const unsigned short gf[N] = {0, 1, 2, 4, 8, 16, 32, 64, 128, 29, 58, 116, 232, 205, 135, 19, 38, 76, 152, 45, 90, 180, 117, 234, 201, 143, 3, 6, 12, 24, 48, 96, 192, 157, 39, 78, 156, 37, 74, 148, 53, 106, 212, 181, 119, 238, 193, 159, 35, 70, 140, 5, 10, 20, 40, 80, 160, 93, 186, 105, 210, 185, 111, 222, 161, 95, 190, 97, 194, 153, 47, 94, 188, 101, 202, 137, 15, 30, 60, 120, 240, 253, 231, 211, 187, 107, 214, 177, 127, 254, 225, 223, 163, 91, 182, 113, 226, 217, 175, 67, 134, 17, 34, 68, 136, 13, 26, 52, 104, 208, 189, 103, 206, 129, 31, 62, 124, 248, 237, 199, 147, 59, 118, 236, 197, 151, 51, 102, 204, 133, 23, 46, 92, 184, 109, 218, 169, 79, 158, 33, 66, 132, 21, 42, 84, 168, 77, 154, 41, 82, 164, 85, 170, 73, 146, 57, 114, 228, 213, 183, 115, 230, 209, 191, 99, 198, 145, 63, 126, 252, 229, 215, 179, 123, 246, 241, 255, 227, 219, 171, 75, 150, 49, 98, 196, 149, 55, 110, 220, 165, 87, 174, 65, 130, 25, 50, 100, 200, 141, 7, 14, 28, 56, 112, 224, 221, 167, 83, 166, 81, 162, 89, 178, 121, 242, 249, 239, 195, 155, 43, 86, 172, 69, 138, 9, 18, 36, 72, 144, 61, 122, 244, 245, 247, 243, 251, 235, 203, 139, 11, 22, 44, 88, 176, 125, 250, 233, 207, 131, 27, 54, 108, 216, 173, 71, 142};
//static const unsigned short fg[N] = {0, 1, 2, 26, 3, 51, 27, 199, 4, 224, 52, 239, 28, 105, 200, 76, 5, 101, 225, 15, 53, 142, 240, 130, 29, 194, 106, 249, 201, 9, 77, 114, 6, 139, 102, 48, 226, 37, 16, 34, 54, 148, 143, 219, 241, 19, 131, 70, 30, 182, 195, 126, 107, 40, 250, 186, 202, 155, 10, 121, 78, 229, 115, 167, 7, 192, 140, 99, 103, 222, 49, 254, 227, 153, 38, 180, 17, 146, 35, 137, 55, 209, 149, 207, 144, 151, 220, 190, 242, 211, 20, 93, 132, 57, 71, 65, 31, 67, 183, 164, 196, 73, 127, 111, 108, 59, 41, 85, 251, 134, 187, 62, 203, 95, 156, 160, 11, 22, 122, 44, 79, 213, 230, 173, 116, 244, 168, 88, 8, 113, 193, 248, 141, 129, 100, 14, 104, 75, 223, 238, 50, 198, 255, 25, 228, 166, 154, 120, 39, 185, 181, 125, 18, 69, 147, 218, 36, 33, 138, 47, 56, 64, 210, 92, 150, 189, 208, 206, 145, 136, 152, 179, 221, 253, 191, 98, 243, 87, 212, 172, 21, 43, 94, 159, 133, 61, 58, 84, 72, 110, 66, 163, 32, 46, 68, 217, 184, 124, 165, 119, 197, 24, 74, 237, 128, 13, 112, 247, 109, 162, 60, 83, 42, 158, 86, 171, 252, 97, 135, 178, 188, 205, 63, 91, 204, 90, 96, 177, 157, 170, 161, 82, 12, 246, 23, 236, 123, 118, 45, 216, 80, 175, 214, 234, 231, 232, 174, 233, 117, 215, 245, 235, 169, 81, 89, 176};

static unsigned short c[E * K + 1] = {0};

//有限体の元の逆数
unsigned short
oinv(unsigned short a)
{
  int i;

  if (a == 0)
    return 0;

  return N-fg[a]+1;
  
  printf("no return \n");

  exit(1);
}

//aに何をかけたらbになるか
unsigned short
equ(unsigned short a, unsigned short b)
{
  int i;

  return gf[mlt(oinv(a),fg[b])];

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

vec vadd(vec a,vec b){
int i;

//#pragma omp parallel for schedule(static)
  for(i=0;i<DEG/4;i++)
    a.y[i]^=b.y[i];

return a;
}


//20200816:正規化したいところだがうまく行かない
//多項式の足し算
OP oadd(OP f, OP g)
{
  //f = conv(f);
  //g = conv(g);
  ////assert(op_verify(f));
  ////assert(op_verify(g));

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
  ////assert(op_verify(h));
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

        //  else{
        // t=s;
        // }
      }
    }
  }
  //  exit(1);

  return s;
}

// 多項式を項ずつ掛ける
vec vterml(vec f, oterm t)
{
  //f = conv(f);
  ////assert(op_verify(f));
  int i;
  vec h = {0};

  // f=conv(f);
  // k = deg (o2v(f));

  for (i = 0; i < DEG; i++)
  {
    //h.t[i].n = f.t[i].n + t.n;
    if(f.x[i]>0)
    h.x[i+t.n] = gf[mlt(fg[f.x[i]], fg[t.a])];
  }

  //h = conv(h);
  // assert(op_verify(h));
  return h;
}

//多項式を項ずつ掛ける
OP oterml(OP f, oterm t)
{
  f = conv(f);
  ////assert(op_verify(f));
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
  //assert(op_verify(h));
  return h;
}

//多項式の掛け算
OP omul(OP f, OP g)
{
  f = conv(f);
  g = conv(g);
  //assert(op_verify(f));
  //assert(op_verify(g));
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
  //assert(op_verify(h));
  return h;
}

// リーディグタームを抽出(default)
oterm vLT(vec f)
{
  int i;
  oterm t = {0};

  // k = deg (o2v (f));
  for (i = 0; i < DEG; i++)
  {
    // printf("a=%d %d\n",f.t[i].a,f.t[i].n);
    if (f.x[i] > 0)
    {
      t.n = i;
      t.a = f.x[i];
    }
  }

  return t;
}

vec vmul_2(vec a, vec b)
{
  int i, j, k, l;
  vec c = {0};

  k = deg(a);
  l = deg(b);

  for (i = 0; i < k+1; i++)
  {
    for (j = 0; j < l+1; j++)
      //if (a.x[i] > 0)
      {
        c.x[i + j] ^= gf[mlt(fg[a.x[i]], fg[b.x[j]])];
      }
  }

  return c;
}

// 多項式を単行式で割る
oterm vLTdiv(vec f, oterm t)
{
  oterm tt = {0}, s = {
                      0};

  tt = vLT(f);
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
    // printf("%u\n",s.a);
  }
  else if (t.n == 0 && t.a > 0)
  {
    s.a = gf[mlt(fg[tt.a], oinv(t.a))];
    s.n = tt.n;
  }

  return s;
}

// 多項式の剰余を取る
vec vmod(vec f, vec g)
{
  vec h = {0};
  oterm b = {0}, c = {0};

//printf("vmod-bl=%d k=%d\n",deg(f),deg(g));
  if (vLT(f).n < vLT(g).n)
  {
    //    exit(1);
    return f;
  }

  b = vLT(g);

//printpol(f);
//printf(" ==f\n");
  while (1)
  {

    c = vLTdiv(f, b);
    h = vterml(g, c);
    f = vadd(f, h);
    if (deg((f)) == 0 || deg((g)) == 0)
    {
      break;
    }

    if (c.n == 0)
      break;
  }
//printf("vmod-baka== %d %d\n",deg(f),deg(g));
  return f;
}


vec vcoef(vec v){
  unsigned short n,k=deg(v);
  int i;

//if(v.x[0]==0)
//return v;

if(v.x[0]>1)
n=oinv(v.x[0]);
for(i=0;i<k+1;i++)
v.x[i]=gf[mlt(n,fg[v.x[i]])];

return v;
}


vec rev(vec a)
{
  vec vx = (a), tmp = {0};
  int k = deg((a)), i;
  OP t = {0};

  //printf("k=%d\n", k);
  // exit(1);
  for (i = 0; i < k + 1; i++)
    tmp.x[k - i] = a.x[i];
  //printpol(tmp);
  //printf("\n");
  // exit(1);

  return tmp;
}

vec deli(vec a,vec b){
int i=0;
OP t;
vec v={0};

for(i=0;i<deg(b);i++)
  v.x[i]=a.x[i];

return v;
}


//モニック多項式にする
vec coeff(vec f)
{
  unsigned short d=vLT(f).a;
  int i, k;

  k = deg((f)) + 1;
  
  for (i = 0; i < k; i++)
    f.x[i] = gf[mlt(fg[f.x[i]], oinv(d))];

  return f;
}

// fg=1
vec kof(vec a,vec b){
  unsigned short u=oinv(b.x[0]),k=deg(a);
  int i;

  for(i=0;i<k+1;i++)
  a.x[i]=gf[mlt(u,fg[a.x[i]])];

  return a;
}


vec vinv(vec a){
  vec v={0},x={0};
  int i;

  x.x[2]=1;
  v.x[0]=1;
  if(a.x[0]>1)
  a=coeff(a);
  
  
  for(i=0;i<9;i++){
  v=vmul_2(vmul_2(v,v),a);
  if(i>0)
  x=vmul_2(x,x);
  v=deli(v,x);
  //printpol(x);
  //printf(" ==ininv\n");
  }
  //a=deli(vmul_2(v,a),x);
  //printpol(a);
  //printf(" ==1?\n");
  //exit(1);
  //a=deli(a,x);
  //printpol(a);
  //printf(" Ah!\n");
//exit(1);

  return v;
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




vec vmod_2(vec v,vec x){
  vec a={0},b={0},c={0},d={0},e={0};
  int k=deg(x),i,l=deg(v);

printf("al=%d k=%d\n",deg(v),deg(x));
if(vLT(v).n<vLT(x).n)
return v;
if(vLT(v).n==vLT(x).n){
v=vadd(v,x);
return v;
}
d.x[0]=1; //oinv(v.x[0]);
//if(k%2==0)
//c.x[2]=1;
//if(k%2==1)
c.x[1]=1;
for(i=0;i<(l-k+1);i++)
d=vmul_2(c,d);
printpol(d);
printf(" ==dd\n");
//printf(" =d;  l=%d, k=%d %d==nazo\n",l,k,l-k+1);
//exit(1);
a=rev(v);
e=rev(x);

b=vinv(e);
e=deli(vmul_2(b,e),d);
if(vLT(e).a!=1){
  printpol(e);
  printf(" fail!\n");
  exit(1);
}

//printpol(b);
//printf(" ==b^-1\n");

a=deli(vmul_2(a,b),d);
a=rev(a);
//printpol(a);
//printf(" ==q\n");
//exit(1);

v=vadd(v,vmul_2(a,x));

return v;
}


vec sand(vec v,vec x){
  vec a={0},b={0},c={0},d={0},e={0};
  int k=deg(x),i,l=deg(v);

printf("v_2-al=%d k=%d\n",deg(v),deg(x));
if(vLT(v).n<vLT(x).n)
return v;
if(vLT(v).n==vLT(x).n){
v=vadd(v,x);
return v;
}
printpol(v);
printf(" ==vx\n");
printpol(x);
printf(" ==mod\n");
//exit(1);

d.x[0]=1; //oinv(v.x[0]);
//if(k%2==0)
//c.x[2]=1;
//if(k%2==1)
c.x[1]=1;
for(i=0;i<(l-k+1);i++)
d=vmul_2(c,d);
printpol(d);
printf(" ==dd\n");
//printf(" =d;  l=%d, k=%d %d==nazo\n",l,k,l-k+1);
//exit(1);
printpol(v);
printf(" ==a\n");
a=rev(v);
e=rev(x);

b=vinv(e);
e=deli(vmul_2(b,e),d);
printpol(e);
printf(" =vinv\n");
//exit(1);
if(vLT(e).a!=1 || deg(e)>0){
  printpol(e);
  printf(" fail!\n");
  exit(1);
}

vec ee={0},gg={0};
gg.x[1]=1;
ee.x[256]=1;
printpol(deli(b,ee));
printf(" ==b^-1\n");
//exit(1);

printpol(vmod(v,x));
printf(" answer\n");
a=deli(vmul_2(a,b),d);
printpol(a);
printf(" ==test\n");
//exit(1);
a=rev(a);
printpol(a);
printf(" ==q\n");
//exit(1);
printpol(v);
printf(" ==vv\n");
//printpol(deli(vmul_2(a,x),ee));
//printf(" ==r\n");
//exit(1);
v=deli((vadd(v,deli(vmul_2(a,x),d))),d);
printpol(v);
printf(" victory\n");
//exit(1);
if(deg(v)>deg(x))
{
  printf("baka %d %d\n",deg(v),deg(x));
  exit(1);
}
return v;
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

OP tbl[K / 2 + 1] = {0};

void table(OP x, OP mod)
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

  table(f, mod);

  return tbl[n];
}

vec vpowmod(vec f, vec mod, int n)
{
  vec v = {0};
  vec ret={0}, s={0}, t={0};

  v.x[0] = 1;
  ret = v;
  while (n > 0)
  {
    // s=inv()
    if (n & 1)
      ret = vmod((vmul_2(ret, f)), mod); // n の最下位bitが 1 ならば x^(2^i) をかける
    f = vmod((vmul_2(f, f)), mod);
    n >>= 1; // n を1bit 左にずらす
  }
  printpol((ret));
  printf(" it be\n");
  exit(1);

  return ret;
}

int fequ(vec a,vec b){
  int k=deg(a),l=deg(b),i;
  if(k!=l)
  return 1;
  for(i=0;i<k;i++)
  if(a.x[i]!=b.x[i])
  return 1;

  return 0;
}

int cnty=0;
vec vpp(vec f,vec mod,int n){
  int i;
  vec t = {0},s={0};
  t = f;
  s=f;

cnty++;
//printpol(f);
//printf(" ==f\n");
//printpol(mod);
//printf(" ==mod\n");

vec c1={0},c2={0};

  //繰り返し２乗法
  for (i = 1; i < n +1; i++){
    c1=t;
    c2=s;
    t = vmod(vmul_2(t, t), mod);
  
  //exit(1);

    s = vmod_2(vmul_2(s, s), mod);

    if(fequ(t,s)==1){
      t=vmod(vmul_2(c2,c2),mod);
    printpol(t);
    printf(" =t\n");
    s=vmod_2(vmul_2(c2,c2),mod);
    //s=coeff(s);
    printpol(s);
    printf(" =s\n");
    printpol(t);
    printf(" =t\n");
    printf("何故なんだ馬鹿野郎！ %d\n",i);
    
    s.x[0]=65535;
    //return s;
    //printpol(c1);
    //printf(" ==c1\n");
    printpol(c2);
    printf(" ==c2\n");
    printf("{");
    for(int j=0;j<deg(c2)+1;j++)
    printf("%d,",c2.x[j]);
    printf("};\n");
    printf("mod={");
    for(int j=0;j<deg(mod)+1;j++)
    printf("%d,",mod.x[j]);
    printf("};\n");
    
    exit(1);
    }

  printpol(t);
  printf(" ===t\n");
  printpol(s);
  printf(" ===s\n");


  }
  /*
  printpol(s);
  printf(" ==s\n");
  if(fequ(t,s)==1){
    printf("cnt=%d\n",cnty);
    exit(1);
  }
*/
  return t;
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

void printsage(vec a)
{
  int i, j, k;
  oterm b;

  printf("poly=");
  for (i = 0; i < DEG; i++)
  {
    if (a.x[i] > 0)
    {
      b.a = a.x[i];
      b.n = i;
      j = v2a(b);
      // printf("%d,==ba\n",b.a);
      // printf ("X**%d+", i); //for GF2
      printf("B('a^%d')*X**%d+", j, i); // for GF(2^m)
    }
  }
}

void fprintsage(vec a, FILE *fp)
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
      // printf("%d,==ba\n",b.a);
      // printf ("X**%d+", i); //for GF2
      if (i == K)
      {
        fprintf(fp, "B('a^%d')*X**%d;", j, i); // for GF(2^m)
      }
      else
      {
        fprintf(fp, "B('a^%d')*X**%d+", j, i); // for GF(2^m)
      }
    }
  }
}


// gcd
vec vgcd(vec xx, vec yy)
{
  vec tt = {0}, tmp, h = {0};

  h.x[0] = 1;
  //h.x[0] = 0;
  if (deg((xx)) < deg((yy)))
  {
    tmp = xx;
    xx = yy;
    yy = tmp;
  }
  tt = vmod(xx, yy);
  while (deg(tt) > 0)
  {
    xx = yy;
    yy = tt;
    if (deg(yy) > 0)
      tt = vmod(xx, yy);
    if (vLT(tt).a == 0)
      return yy;
  }
  if (vLT(tt).a == 0)
  {
    return yy;
  }
  else
  {
    return h;
  }
  //  return yy;
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
static void
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

//配列からベクトル表現の多項式へ変換する
vec Setvec(int n)
{
  int i;
  vec v = {0};

  for (i = 0; i < n; i++)
  {
    v.x[n - 1 - i] = c[i];
  }

  return v;
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

OP ww[T] = {0};

//配列の値を係数として多項式に設定する
OP setpol(unsigned short f[], int n)
{
  OP g;
  vec a;

  memset(c, 0, sizeof(c));
  memcpy(c, f, 2 * n);
  a = Setvec(n);

  g = v2o(a);

  return g;
}

OP mkpol()
{
  int i, j, k, flg, ii = 0;
  OP w = {0};
  static unsigned short g[K + 1] = {0};

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
  OP uu;
  vec s = {0}, u = {0}, r = {0};
  vec v = {0}, ff=o2v(f);
  //if GF(8192) is 2^m and m==13 or if GF(4096) and m==12 if GF(16384) is testing
  //int m = E;
  // m=12 as a for GF(4096)=2^12 defined @ gloal.h or here,for example m=4 and GF(16)

  v.x[1] = 1;
  s = (v);
  //for (i = 0; i < K / 2; i++)
  r = s;
  n = deg((ff));

  if (vLT(ff).n == 0 && vLT(ff).a == 1)
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
    printf(":i=%d",i);
    // irreducible over GH(8192) 2^13
    r = (vpp(r, ff, E));
    if(r.x[0]==65535)
    return -1;
    u = vadd(r, (s));
    u = vgcd(ff, u);

    if (deg(u) > 0)
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

unsigned short dd[N][N] = {0};

void get_irrpoly(void)
{
  int i, j, l, ii = 0;
  OP w = {0};
  FILE *fp;
  unsigned short ta[N] = {0};

  j = 0;
  fp = fopen("dat.sage", "w");

aa:

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
      goto aa;
      //exit(1);
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
  fprintsage(o2v(w), fp);
  fprintf(fp, " print(poly.is_irreducible());\n");
  j++;

  if (j > 10)
  {
    fclose(fp);
    exit(1);
  }
  goto aa;
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
        fprintsage(o2v(w), f1);
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
        fprintsage(o2v(x), f2);
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
        fprintsage(o2v(y), f3);
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
        fprintsage(o2v(z), f4);
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
  //unsigned short f[K + 1] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 0}; //big indian
    unsigned short f[5] = {11,2,123, 115, 1113}; //big indian
    unsigned short h[9] = {133,1, 1, 15,12,13,14,15,1211};
    vec ww={1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3817,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,217,0,0,0,0,0,0,0,6873,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5646,0,0,0,0,0,0,0,0,2436,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6389,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3345,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7529,0,0,0,7840,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2471};
    vec xx={1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3817,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,217,0,0,0,0,0,0,0,6873,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5646,0,0,0,0,0,0,0,0,2436,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6389,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3345,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7529,0,0,0,7840,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2471,0,0,0,0,0,0,0,0,0,0,1,};
    OP g,w;
    int i,count=0;
    vec e[10]={0},v={0},x={0},z={0};
    int l = -1;
    int ii = 0;
    // irreducible goppa code (既役多項式が必要なら、ここのコメントを外すこと。)


   printpol(ww);
   printf(" ==right?\n");
   x=vmod(vmul_2(ww,ww),xx);
   v=vmod_2(vmul_2(ww,ww),xx);
   printpol(x);
   printf(" ==vmod\n");
   printpol(v);
   printf(" ==vmod_2\n");
   printpol(vmul_2(ww,ww));
   printf(" ==double\n");
   //exit(1);

    g=setpol(f,sizeof(f)/2);
    z=o2v(g);
    v=coeff(z);
    //v=o2v(g);
    printpol(o2v(g));
    printf(" =g1\n");
    w=setpol(h,sizeof(h)/2);
    printpol(o2v(w));
    printf(" =w\n");
    x=o2v(w);
    
    while(ii<1){
    printpol(vmod(x,v));
    printf(" ==vmod\n");
    ii++;
    }
    //exit(1);
    
   ii=0;
   while(ii<1){
    printpol(vmod_2(x,v));
    printf(" ==vmod2\n");
    ii++;
   }
    //exit(1);
    
    v=o2v(g);
    v=coeff(v);
    printpol(v);
    printf(" =g2\n");
    //ii=gf[mlt(fg[3],fg[8182])];

    //exit(1);
    vec dd={0};
    //v=o2v(g);
      printpol(v);
      dd.x[deg(v)*deg(v)]=1;
      printf(" origin\n");
      x=vinv(v);
      printpol((x));
      printf(" =inv[origin]\n");
      printpol(deli(vmul_2(x,v),dd));
      printf(" ==ans\n");
      //    printf("ans=%d\n",ii);
    //exit(1);

    while (l == -1)
    {
        w = mkpol();
        l = ben_or(w);
        printf("irr=%d\n", l);
        if(l==0)
        printsage(o2v(w));
        
        if (ii > 300)
        {
            printf("too many error\n");
            exit(1);
        }
        ii++;
        //
    }
  exit(1);

  //test , usage and example
  for (i = 0; i < N; i++)
  {
    memset(&g ,0,sizeof(g));
    f[K] = i;
    g = setpol(f, K + 1);
    if (ben_or(g) == 0)
    {
      printsage(o2v(g));
      printf(" is irreducible %d\n",i);
      count++;
      if(count==10)
      exit(1);
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
