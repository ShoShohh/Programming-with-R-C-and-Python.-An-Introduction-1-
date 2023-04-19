/*
参考ウェブページURL：1.https://webkaru.net/clang/matrix-multiplication/
                   2.https://ja.stackoverflow.com/questions/68131/c%e8%a8%80%e8%aa%9e%e3%81%a7%e3%81%ae%e8%a1%8c%e5%88%97%e8%a1%a8%e7%a4%ba
工夫したところ：始めに定義する最大の次元数を超えるような次元数が入力された場合，再入力を求めるようにした．そして，入力を求める際に最大の次元数を表示するようにしている（各次元数は一致するものとしている）．
また，プログラムの読みやすさのため，最大の次元数とプログラム内で定義するその値（L, M, N）が一致するようにしている．この場合，for文内で扱う添え字と通常考える行列の添え字が一致しないが，等号を含まない不等号を用いるように注意することで問題が起こらないようにしている．
参考ウェブページの一つ目を参考にして行列の積を計算しているが，ウェブページでは無駄な処理があったため削っている．注意として，このプログラムだと入力された次元数を超える/満たない行数や列数で行列が入力されても実行は出来てしまう．実際は行っていないが，入力された次元数を超える/満たないような行数・列数で行列が入力されたときに再入力を求めるようにもできる．
次元数に対して改行が遅く/早く入力されたときに上記と同じように再入力を求めれば良い．
*/

#include <stdio.h>
#define L 100
#define M 100
#define N 100

int main(void){
    double A[L][M], B[M][N], C[L][N];
    int l, m, n;
    int i, j, k;
    double term;
    
    printf("Input dimentions of two matrices (each dimention is %d or less): ", L);
    scanf("%d" "%d" "%d", &l, &m, &n);
    if(l > L||m > M||n > N){
      printf("Input dimentions of two matrices again (each dimention is %d or less): ", L);
      scanf("%d" "%d" "%d", &l, &m, &n);
    }

    printf("\nInput Matrix A : \n");
    for(i = 0;i < l;++i){
      printf("A[%d] = ", i + 1);
      for(j = 0;j < m;++j){
        scanf("%lf", &A[i][j]);
      }
    }

    printf("\nInput Matrix B : \n");
    for(i = 0;i < m;++i){
      printf("B[%d] = ", i+1);
      for(j = 0;j < n;++j){
      scanf("%lf", &B[i][j]);
      }
    }

    printf("\nDimentions of two matrices : %d %d %d\n", l, m, n);
    printf("\nMatrix A =\n");
    for (i = 0; i < l; i++){
      printf(" ");
      for (j = 0; j < m; j++){
         printf(" %lf", A[i][j]);
      }
      printf("\n");
    }

    printf("\nMatrix B =\n");
    for (i = 0; i < m; i++){
      printf(" ");
      for (j = 0; j < n; j++){
         printf(" %lf", B[i][j]);
      }
      printf("\n");
    }

    for(i = 0;i < l;i++){
      for(j = 0;j < n;j++){
        term = 0;
        for(k = 0;k < m;k++)
          term = term + A[i][k] * B[k][j];
        C[i][j] = term;
      }
    }
 
    printf("\nMatrix C = A * B =\n");
    for (i = 0; i < l; i++){
      printf(" ");
      for (j = 0; j < n; j++) {
        printf(" %lf", C[i][j]);
      }
      printf("\n");
    }

    return 0;
}