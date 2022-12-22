/*
500093679 clang baka
1014871759 gcc baka
2359215758 gcc ba
637637269 clang ba
853722722 clang vmul
853722722 gcc vmul
*/

typedef struct {
  vec a;
  vec b;
  vec c;
} tri;

tri wake(vec x, int D){
  int i;
  tri v;
  for(i=0;i<D;i++){
    v.a.x[i]=x.x[i];
    v.b.x[i]=x.x[i+D];
    v.c.x[i]=x.x[i]^x.x[i+D];
  }

  return v;
}


tri kake(tri x,tri y){
tri t;

t.a=vmul_2(x.a,y.a);
t.b=vmul_2(x.b,y.b);
t.c=vadd(vadd(vmul_2(x.c,y.c),t.a),t.b);
return t;
}

vec tas(tri n,int D){
  int i;
  vec e={0};

  for(i=0;i<D*2;i++){
  e.x[i]^=n.a.x[i];
  e.x[i+D*2]^=n.b.x[i];
  e.x[i+D]^=n.c.x[i];
  }
//printpol(n.c);
//printf("==eeeee\n");
//exit(1);

  return e;
  
}

vec kara(vec a,vec b){
  tri z,w,c,za,zb,zc,a1,a2,a3,b1,b2,b3,c1,c2,c3,d1,d2,d3;
  tri za1,za2,za3,zb1,zb2,zb3,zc1,zc2,zc3;
  tri aa1,aa2,aa3,bb1,bb2,bb3,cc1,cc2,cc3;
  tri x1,x2,x3,v1,v2,v3,w1,w2,w3,s1,s2,s3;
  vec d;
  int i;

  z=wake(a,128);

  //za=wake(z.a,64);
  //zb=wake(z.b,64);
  //zc=wake(z.c,64);

  w=wake(b,128);
  
  aa1=wake(w.a,64);
  aa2=wake(w.b,64);
  aa3=wake(w.c,64);

  /*
  a1=wake(za.a,32);
  a2=wake(za.b,32);
  a3=wake(za.c,32);
  b1=wake(za.a,32);
  b2=wake(za.b,32);
  b3=wake(za.c,32);
  c1=wake(zc.a,32);
  c2=wake(zc.b,32);
  c3=wake(zc.c,32);


  za1=wake(aa1.a,32);
  za2=wake(aa1.b,32);
  za3=wake(aa1.c,32);
  zb1=wake(aa2.a,32);
  zb2=wake(aa2.b,32);
  zb3=wake(aa2.c,32);
  zc1=wake(aa3.a,32);
  zc2=wake(aa3.b,32);
  zc3=wake(aa3.c,32);

  x1=kake(a1,za1);
  x2=kake(a2,za2);
  x3=kake(a3,za3);
  v1=kake(b1,zb1);
  v2=kake(b2,zb2);
  v3=kake(b3,zb3);
  w1=kake(c1,zc1);
  w2=kake(c2,zc2);
  w3=kake(c3,zc3);
  tri o1,o2,o3,p1,p2,p3,q1,q2,q3;
  vec ans={0},cf={0};

  o1.a=tas(x1,64);
  o1.b=tas(x2,64);
  o1.c=tas(x3,64);
  o2.a=tas(v1,64);
  o2.b=tas(v2,64);
  o2.c=tas(v3,64);
  o3.a=tas(w1,64);
  o3.b=tas(w2,64);
  o3.c=tas(w3,64);
  p1.a=tas(o1,128);
  p1.b=tas(o2,128);
  p1.c=tas(o3,128);

  ans=tas(p1,256);
  cf=vmul_2(a,b);
  for(i=0;i<512;i++)
  if(ans.x[i]!=cf.x[i]){
    printf("i=%d %d %d\n",i,ans.x[i],cf.x[i]);
  }
  exit(1);
*/  
  c=kake(z,w);
  d=tas(c,128);
  //printpol(d);
  //printf("====ddddd\n");
  //exit(1);

return d;
}



