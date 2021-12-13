# ben_or_irreducible_poly

cf.https://digitalcommons.iwu.edu/cgi/viewcontent.cgi?article=1013&context=math_honproj

阿吽酸数値計算

# example

```c

int main(void)
{
  unsigned short f[K + 1] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 0}; //big indian
  OP g;
  int i;

  //test , usage and example
  for (i = 0; i < N; i++)
  {
    memset(&g, 0,sizeof(g));
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
# 20211207

初期化忘れでした。

ここ数日はvscodeの新規ファイル消失事件の対応でなかなか進まなかった。

結局vscodeのバグだと分かってバージョンダウンして対応した。

システム再構築まで考えたけど最終的にバグで済んでよかった。

自分一人だけで何一つ有益なアドバイスをもらえないなかで、自力で情報を見つけられたのはよかった。

プログラムは一応分割コンパイルっぽくできたし、Wallオプション付けても警告出ないし、
一応指摘されたことはしているんじゃないかと思うんですがまだほかにもあるんでしょうか・・・。

ピクシブみたいに自分のフリーソフトにお布施を募集することができればいいのにとスポンサーなるアカウントを作ろうとしたけど英語がわからなくて諦めた。

一応貢献していると認められているので、募集してもいいんだけど何かいい方法ないんだろうか。

海外送金になるから外国に税金の申告しないといけないかもしれないし、
お金の管理とか面倒になりそうだからやめた。

# 20211201

自分にとっては、このくらいの量のプログラムを完璧にするくらいが丁度いいようです。

ほかにも作りたいプログラムはありますが、シングルフォーカス特性のためにそれができてないです。

# 20211130

有限体上の多項式の既約性判定テストの実装

