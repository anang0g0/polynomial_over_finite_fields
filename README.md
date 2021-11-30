# ben_or_irreducible_poly

# Usage

```c

int main(void)
{
  time_t t;
  unsigned short f[K + 1] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 0}; //big indian
  OP g;
  int i;

  srand(clock() * time(&t));

  //test , usage and example
  for (i = 0; i < N; i++)
  {
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

  return 0;
}

```

# 20211130

有限体上の多項式の既約性判定テストの実装

# 20211201

自分にとっては、このくらいの量のプログラムを完璧にするくらいが丁度いいようです。

ほかにも作りたいプログラムはありますが、シングルフォーカス特性のためにそれができてないです。
