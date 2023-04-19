/*
参考にした本：新・明解C言語入門編（柴田望洋）List4-14(p.94)
工夫したところ：まず簡単に出力について工夫したところは，自然数の入力と合計の出力がわかりやすいように"Natural Number : "と"Sum : "を表示するようにした．変数nについて，long int型で定義しているが（longに省略可能），10^9ならint型で定義しても問題はない．short型で定義してしまうと10^6からオーバーフローを起こすため（int型は通常プラマイ2.1*10^9程度まで，long型は通常プラマイ91.1*10^9程度まで，short型は通常プラマイ3.2*10^4程度まで表現可能），int型かlong型で定義する工夫が必要だった．
次に変数iとxだが，足される数xと足す数1/iについて情報落ちに注意しなければならない．足される数ｘは0から始まり，まず1/i=1/1=1を足される．そこから足す数1/iは1/2,...と絶対値がxの絶対値に比べて小さくなっていくため情報落ちがこの和算において起こる．具体的には，iが大きくなるにつれて1/iが段々と小さくなり，(xに)定義された型の表現範囲を超えた小数の値になったときにxとの和算において末端の部分が切り捨てられて和算の結果が元と変わらないような情報落ちが起こる．
情報落ちが起こるのを遅くするために，変数iとxの型を出来るだけ大きい表現範囲を持つ同じ型で定義した．double型（二倍精度）は2進53桁（10進15桁程度）が表現可能であり，float型（単精度）の2進24桁（10進7桁程度）よりも表現可能な範囲が広く，double型を使うことで情報落ちが遅くなるように工夫した（long double型（四倍精度）もあるが，それは処理系によって出力が安定しなかったので使わなかった．）．例えば，変数iをdouble型で定義して変数xをfloat型で定義すればより早く情報落ちが起こる（もしくは共にfloat型で定義したり，変数iをfloat型で，変数xをdouble型で定義すればより早く情報落ちが起こる．
ただし，これは表現可能な範囲をそれぞれの変数で超えて末端が切り捨てられるため，和算による情報落ちとは厳密には言えないように思う．共にdouble型で定義した場合も同様である．）．この情報落ちがわかるように合計の値は下8桁まで表示するように工夫した．変数xをfloat型で定義していれば，"Natural Number"として100程度の小さい値を入力しても下6桁目以降で情報落ちが起こり，下記の実行結果より小さい値が出力される．
*/

#include <stdio.h>

int main(void)
{
	long int n;
	double x = 0;
	double i = 1;

	printf("Natural Number : ");scanf("%d", &n);

	while(i <= n){
		x += 1 / i;
		i++;
	}
	
	printf("Sum : %.8lf", x);

	return 0;
}