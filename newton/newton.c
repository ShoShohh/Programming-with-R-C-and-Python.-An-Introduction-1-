/*
参考ウェブページURL：https://tsunelab-programming.com/alg-newton
工夫したところ：初期値入力の後に何度もプログラムを実行する手間を省くため，与えられた初期値で近似解が収束した後に他の近似解が欲いのかを確認するようにした．
そこで他の近似解が欲しいと入力された場合，初期値を再入力するように表示している．
また，これらの工夫においてはプログラムの終了がわかりにくいため，プログラムの終了がわかりやすいような表示をするように工夫した．
再帰的にニュートン法の関数を定義することで，与えられた初期値で近似解が収束しなかった場合に初期値を再入力するように求め，その初期値で再度ニュートン法を適用するように工夫した．
*/

#include <stdio.h>
#include <math.h>
#define EPS 1E-8 /* 要求精度 */
#define LIMIT 50 /* 繰り返し回数の上限 */

double f(double x){ /* 近似解を求めたい方程式の関数 */
    return  ((x) * (x) * (x) * (x) * (x)
            - 2.4 * (x) * (x) * (x) * (x) 
            + 2.7 * (x) * (x) * (x)
            - 1.6 * (x) * (x)
            + 2.4 * (x)
            - 14);
}

double g(double x){ /* 近似解を求めたい方程式の関数の導関数 */
    return (5 * (x) * (x) * (x) * (x)
           - 4 * 2032.4341213934738 * (x) * (x) * (x)
           + 3 * 25174.794100030227 * (x) * (x)
           - 2 * 117014.62888983989 * (x)
           + 241443.476813119);
}

/* ニュートン法を再帰的に行えるような関数 */
void newton(double x){
    double dx;
    int k, check;

    for(k = 1;k <= LIMIT;k++){ /* kの増加に合わせて，設定した繰り返し回数の上限までは近似解となる点列を求めていく． */
        dx = x; /* 現段階の近似解 */
        x = x - f(x) / g(x); /* ニュートン法により求める次の近似解 */

        /* 近似解の差の絶対値を現段階の近似解の絶対値で割り，それが設定した要求精度より小さければ次の近似解を得られた近似解として表示する． */
        if( fabs(x - dx) < fabs(dx) * EPS ){ 
            printf("x=%lf\n", x);
            /* 他の近似解を求めたければ'1'を，終わりでよければ'0'を入力させる． */
            printf("If you want more solutions, enter '1'; if not, enter '0'. :");
            scanf("%d", &check);
            if(check == 1){
                printf("\nInput a initial value x0. :");
                scanf("%lf", &x);
                newton(x); /* 再度入力された初期値でnewton関数を呼び出す． */
            }
            else if(check == 0){
                printf("\nEnd."); /* 終了するように入力されたら，"End."と表示してプログラムを終了する． */
                break;
            }
            break;
        }
    }
    
    /* 試行回数が設定したLIMITよりも大きくなってしまえば近似解が収束しなかったと判断し，収束しなかったと表示する． */
    /* そして，初期値を再入力させる． */
    if( k > LIMIT ){
        printf("The solution did not converge. Input the other initial value x0. :");
        scanf("%lf", &x);
        newton(x); /* 再度入力された初期値でnewton関数を呼び出す． */
    }
}

int main()
{
    double x;

    printf("Input a initial value x0. :");  /* 初期値の入力を求め，xに初期値を代入する． */
    scanf("%lf", &x);

    newton(x);

    return 0;
}