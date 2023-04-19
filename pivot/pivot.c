/*
参考ウェブページURL：http://computational.pc-physics.com/gauss.html
工夫したところ：細かな解説や動作についてはコメントで挿入している．
前進消去（Forward Elimination）後の行列Aとベクトルbを表示するようにした．直接データを入力する際に入力しやすくするため，"A[1]="等を出力するように工夫している．しかし，リダイレクトでデータを渡す場合には少し邪魔に見える．
行列Aとベクトルbの入出力時に列数の固定を行うことで，拡大係数行列として配列Aを簡単に処理できるように工夫した．
*/

#include <stdio.h>
#include <math.h>
#define L 100

int main(void){
  double A[L][L + 1]; /* 行列Aを拡大係数行列として処理するために列数を多く定義している． */
  double x[L];

  int i, j, k, l, s, pivot;
  double p, q, m, temp[L + 1];
    
  /* 行列A及びベクトルbの次元とその要素の入力を求め，リダイレクトによるデータの入力や直接入力がされたらそれらを表示する． */
  printf("Input a dimention of a matrix A (and a vector b)(each dimention is %d or less): ", L);
  scanf("%d", &l);
  if(l > L){
    printf("Input a dimention of a matrix A (and a vector b)(each dimention is %d or less): ", L);
    scanf("%d", &l);
  }

  printf("\nInput a matrix A : \n");
  for(i = 0;i < l;++i){
    printf("A[%d] = ", i + 1);
    for(j = 0;j < l;++j){
      scanf("%lf", &A[i][j]);
    }
  }

  /* 実際は拡大係数行列の一部としてベクトルbを入出力している． */
  printf("\nInput a vector b : \n");
  for(i = 0;i < l;++i){
    printf("b[%d] = ", i + 1);
    scanf("%lf", &A[i][l]);
    }

  printf("\nA dimention of the matrix A (and the vector b): %d\n", l);
  printf("\nThe matrix A =\n");
  for (i = 0; i < l; i++){
    printf(" ");
    for (j = 0; j < l; j++){
       printf(" %lf", A[i][j]);
    }
    printf("\n");
  }

  printf("\nThe vector b =\n");
  for (i = 0; i < l; i++){
    printf("  %lf", A[i][l]);
    printf("\n");
  }

  /* ピボット選択付きガウス消去法による解の導出． */
  for(i = 0;i < l;i++) {
    m = 0;
    pivot = i;

    /* i-1列まで前進消去が終ったとき，i列の中で要素の値がが一番大きい行を選ぶ． */
    /* 変数sが行を，変数iが列を司る．iを固定してsを走らせ，i列の中で一番大きな値のある行を探す． */
    for(s = i;s < l;s++) {
      if(fabs(A[s][i]) > m) {
        m = fabs(A[s][i]);
        pivot = s;  /* このpivotは行列の成分ではなく，行数を表す．（講義ではpivotが成分だったため注意が必要）*/
      }
    }

    /* pivotがiと違えば，つまりi列目のi行目の要素よりも大きい値があれば，その行とi行を入れ替える．（pivotが行数を表すことに注意） */
    if(pivot != i) {  
      for(j = 0;j < l + 1;j++){
        temp[j] = A[i][j];        
        A[i][j] = A[pivot][j];
        A[pivot][j] = temp[j];
      }
    }
  }

  /* 前進消去によって係数行列を上三角行列にする． */
  for(k = 0;k < l;k++) {
    p = A[k][k];  /* 行列A（係数行列と見て）の対角要素を保存する． */
    A[k][k] = 1;  /* 対角要素は1になることがわかっている（そう処理される）ので直接1を代入する． */    
    for(j = k + 1;j < l + 1;j++) {  /* 拡大係数行列として行列Aが入力されているから，ベクトルbに対する処理として"j=l"まで処理する． */
      A[k][j] /= p; /* 拡大係数行列のk行目（行列A及びベクトルbのk行目）を行列Aのk番目の対角成分で割る． */
    }
    /* 対角成分を1にした次の行にて，1にした成分と同じ列にある要素と前の行の要素の積を要素から引いていく． */
    /* わかりにくいが，要は対角成分を1にしてその下の要素を0にするための行基本変形． */
    for(i = k + 1;i < l;i++) {
      q = A[i][k];
      for(j = k + 1;j < l + 1;j++) {
        A[i][j] -= q * A[k][j];
      }
      /* 前の処理で1にした対角成分と同じ列にある成分は0となることがわかっている（そう処理される）ので直接0を代入 */
      A[i][k] = 0;
    }
  }

  /* 後退代入による解の計算． */
  for(i = l - 1;i >= 0;i--) {
    x[i] = A[i][l]; /* 求めたい解にまず前進消去後のベクトルbの値を代入する（前進消去により係数行列の対角成分が1となっていることに注意）． */
    for(j = l - 1;j > i;j--) {
      x[i] -= A[i][j] * x[j]; /* 求まった添え字番号後ろ側の解の値と，それに対応する前進消去後の係数行列Aの要素の積の値を
                                  前進消去後のベクトルbの要素から引く．（つまり解についての方程式を解く） */
    }
  }

  /* 前進消去後の係数行列Aとベクトルbを表示している． */
  printf("\nThe matrix A (after Forward Elimination)=\n");
  for (i = 0; i < l; i++){
    printf(" ");
    for (j = 0; j < l; j++){
       printf(" %lf", A[i][j]);
    }
    printf("\n");
  }

  printf("\nThe vector b (after Forward Elimination)=\n");
  for (i = 0; i < l; i++){
    printf("  %lf", A[i][l]);
    printf("\n");
  }

  /* 解の表示 */
  printf("\nA solution x (of the linear equation A*x=b) =\n");
  for (i = 0; i < l; i++){
    printf("  %lf", x[i]);
    printf("\n");
  }

   return 0;
}