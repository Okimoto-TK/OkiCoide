#include <stdio.h>
using namespace std;
long long n;
struct matrix
{
    long long a[2][2];
    matrix(){
        a[0][0] = 1;
        a[0][1] = 0;
        a[1][0] = 0;
        a[1][1] = 1;
    }
    void print(){
        printf("%d %d\n", a[0][0], a[0][1]);
        printf("%d %d\n", a[1][0], a[1][1]);
    }
};
matrix matrixTimes(matrix a, matrix b, long long p){
    matrix r;
    r.a[0][0] = (a.a[0][0] * b.a[0][0] + a.a[0][1] * b.a[1][0]) % p;
    r.a[0][1] = (a.a[0][0] * b.a[0][1] + a.a[0][1] * b.a[1][1]) % p;
    r.a[1][0] = (a.a[1][0] * b.a[0][0] + a.a[1][1] * b.a[1][0]) % p;
    r.a[1][1] = (a.a[1][0] * b.a[0][1] + a.a[1][1] * b.a[1][1]) % p;
    return r;
}
matrix matrixMod(matrix a, long long p){
    a.a[0][0] %= p;
    a.a[0][1] %= p;
    a.a[1][0] %= p;
    a.a[1][1] %= p;
    return a;
}
matrix matrixPow(matrix o, long long k, long long p){
    matrix r;
    while(k != 0){
        if(k & 1){
            r = matrixTimes(r, o, p);
            r = matrixMod(r, p);
        }
        o = matrixTimes(o, o, p);
        o = matrixMod(o, p);
        k /= 2;
    }
    return r;
}
int main(int argc, char const *argv[])
{
    scanf("%lld", &n);
    if(n <= 2)
        printf("1");
    else{
        matrix init;
        init.a[0][0] = 1;
        init.a[0][1] = 1;
        init.a[1][0] = 1;
        init.a[1][1] = 0;
        matrix ans = matrixPow(init, n - 2, 1000000007);
        printf("%d", (ans.a[0][0] + ans.a[0][1]) % 1000000007);
    }
    return 0;
} 