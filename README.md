# ben_or_irreducible_poly

cf.https://digitalcommons.iwu.edu/cgi/viewcontent.cgi?article=1013&context=math_honproj

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

# 20221204

既約多項式の次数が256の場合をどうやって一発で見つけるかが問題だったのですが、Kuboonさんが見つけてきた資料から重大なヒントをもらって、それをもとに

$$ F(Y)=Y^{256}+Y^{241}+Y^{178}+Y^{121}+1 $$

を法とする多項式でmodを取ればいいことに気がついて実際やってみたら、一発で次数２５６の最小多項式を見つけることができました。

（行列の方ではない）体論で言うところの最小多項式は常に既約なのですが、理論的な背景はこれから進めていきたいと思います。

これを使えば、現在進行中のPQC選考会で出されているClassic McElieceの安全性パラメータよりつよつよな暗号化が可能になります。

# 20221129

カラツバ法にバグを発見。
同じ関数をかけたときだけ正しい。
違う関数をかけると間違える。
手計算で計算するのはもう限界なので、分け算関数と掛け算関数と足し算関数の3つに分けてモジュール化した。

しかし未だに完全に動作原理を理解してないらしく、1段目はうまく行くけど2段目以降は失敗する。
でもこの1段関数なら異なる関数でも計算できるので、2重ループの掛け算関数より3/4だけ早く計算することができる。

今後さらにモジュール化して、多段関数をできるようにする。

> 20221205：追記

> モジュール化したけど、2段めまでしか高速になりませんでした。
> 3段目で遅くなり、高速化の効果は2段まででした。
> それでも2/3くらい早くなったので効果があったことになります。
> FFTもやったほうがいいのかもしれないです。


# 20221128

カラツバ法を実装しました。gccとclang では挙動が違いますが、プログラムの負担に比べれば効果がほんの少し、数％の高速化しかできないのが謎です。
なにかいい方法はないだろうか？

# 20221107

ニュートン法完成。しかし遅い。2，5倍くらい遅い。

原因は割り算の中で多項式の掛け算を使っているためと思われる。

つまり、多項式の次数 $N$ に対して2重ループになっているためで、 $N^2$ になっているからだと思う。

これをFFTを使って $N log(N)$ まで減らすことができればもっと早くなるのではないかと思う。

使ってない関数を減らしたら、半分くらいになった。（1200行くらい）

# 20221106

ニュートン法を使った割り算ができた、と思ったらまだバグがあった。
中途半端に正しいのは紛らわしい。

動かすことができるまでに3日もかかったけど、まだ完成しない。
以前のは動いているように見えただけで、バグチェックをするととたんに出来損ないがわかった。
動いている関数と混ざらないように、元ファイルをコピーしてそこで作業した。

最初は関数のサンドボックスのつもりでsand関数を作ったのだが、それもなんだかうまく行かなくてjorju関数にしたらうまく行ったｗ

ジョルジュサンド知ってる人どのくらいいるんだろうｗ

問題は速度。
3日も費やしたのに、普通の割り算関数のほうが30倍くらい早いｗ

掛け算はFFTを使う予定だけど、きちんと理解してないと他の人が作った関数も使えない状態なので勉強せねばならない。
いらない公司も削除しないといけないし、るばーとさんを待たせるのも失礼かも。

ああ、でもFFTやりたい。
遅い原因を特定したい。
gproffを見てみよう。（実は今のバグはgproffを見ていてまだvmod関数が動いていることを知ったからで、バグの発見に間接的に役立ったことになる）

ゴールはまだ先である。

# 20221105

割り算は完成したけど速度が遅い。もっと効率的にしないとだめだし、パラメータを変えても動くようにしないといけない。

cf．ハードウェア的鍵生成の資料　 https://eprint.iacr.org/2017/595.pdf

# 20221102

ちょっと今いじってる最中で、完成版はven-or.cになる予定です。

venはbenに比べて素晴らしく高速で、どこかの論文に書いてあったように受け入れられないほどコストがかかるというのは本当だろうかという感じもします。
ランダムに係数を選ぶと、大体５秒位で既約多項式が見つかります。

今はまだ割り算速度の改良中で、vmod_2関数の計算結果に問題があるので、それをクリアしたら次は掛け算のFFT処理に入ります。
最終的にはもう少し早くなってくれればいいなと思っています。

これは最初の設計ミスで、多項式型OPは採用しないほうが良かったという感じです。
というのも、ベクトル型で処理する関数と混在しているため、相互の変換関数であるo2vやv2oなどの不被通用な処理に時間がかかっているからです。

これが多変数多項式で、メモリをなるべく節約したいならOP型もあると思うのですが、どうせやるにしても代数曲線までなので２変数で十分です。
２変数多項式のベクトル表現は、次数 $n$ に対して $n^2$ の行列になるなどメモリ資源の観点から問題がないとは言えないにしても、計算結果が必ず正規化されるという意味で便利です。

私がこの計算の最適化や高速化をするようになったきっかけは光成滋生さんのXybakのせいですｗ

あと少しで出来上がるんですが、できそうでできないのがもどかしい。

# 20221031

多項式の規約性判定アルゴリズムの改良をした。
具体的にはben_or関数をベクトル型に統一して、並列計算ができるようにした。

もう一つは重要なことだが、逆元を計算したり、かけるとある値と同じになる数の計算に、
何も考えないでループを回すなど、あまりにもアホな実装だったので、Zech対数の原理から一回で値を返すように変えたら100倍くらい高速になった。
800個の多項式を14秒で既約性判定できるようになった。

これで鍵生成も怖くなくなった。

あとはあまり呼び出す回数の少ない関数の改良で、割り算掛け算をそれぞれニュートン法とFFTで高速化できないかどうかを試す予定。

残りはマルチコアに対応させるための処理を導入するかどうか。
これをやらないと現時点でパソコンの性能を活かせないことになるので、ぜひとも対応させたい。

McEliece暗号の欠点としては、公開鍵のサイズがでかすぎるという1点のみで、他の要素は優れているのに、使わないのはもったいないと思う。

# 20221029

多項式の逆源の実装をしてました。

正直法のない有限退場の多項式に、逆源があるとは思いませんでした。
今までやっていた逆源はGCDを計算する過程での副産物としてだったのですが、
今度は関数地の近似会を求めるニュートン法に基づく逆数計算だとしって、そんな方法でもできるのかと半信半疑で実装してます。
とりあえず今日は逆元の計算のところまで。

逆数が計算できれば、それを割りたい数にかければ割り算になるし、剰余も引き算すればできるというので、今までの方法とどちらが早いか期待してます。
今までの方法だと割り算だけ異様に遅くて、 $O(N^2)$ くらいかかるけど、今度実装しているのはニュートン法の割り算と、FFTを使った掛け算なので、
 $O(N log N)$ くらい早くなることが期待できます。

どの程度性能が上がるかはお楽しみです。（全く上がらない気もするがｗ）

今日はもう限界です。動くのが欲しい人は　ben-or.c　の一つ前のバージョンで動かしてみてください。
今日のアップロードは自分用です。

ていうか誰も見てないし、見てないなら1変数多項式計算での光成茂雄を目指そうみたいな感じでｗ

# 20221028

生まれ変わるなじゃないかというほどエレガントな計算方法を見つけたので、明日から開発を再開します。

ます割り算は、逆元を高速に演算できれば高速化できるし、いい加減なバグだらけの今までの曖昧な停止条件に頼らなくてもニュートン法を使えば瞬殺で計算できる。
割り算は逆元をかければいいだけなので、更に高速化できる。

掛け算はシュトラッセン法という $O(NlogNloglogN)$ で終わる掛け算を使えば、今まで次数 $N$ の多項式を計算するのに $O(N^2)$ 回計算していたのが $O(N)$ くらいで計算できる。
これで生まれ変わりは確実！

ではごきげんようｗ


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

