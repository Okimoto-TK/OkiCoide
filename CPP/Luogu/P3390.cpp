#include <stdio.h>
#include <string.h>
using namespace std;
const int Mod = 1000000007;
int n;
struct matrix
{
    long long value[100][100];
    matrix(){
        for(int i = 0; i < 100; i ++)
            for(int j = 0; j < 100; j ++)
                value[i][j] = 0;
        for(int i = 0; i < 100; i ++)
            value[i][i] = 1;
    }
};
matrix matrixMultiplication(matrix a, matrix b){
    matrix result;
    for(int i = 0; i < n; i ++){
        for(int j = 0; j < n; j ++){
            result.value[i][j] = 0;
            for(int k = 0; k < n; k ++){
                result.value[i][j] = result.value[i][j] % Mod + a.value[i][k] % Mod * b.value[k][j] % Mod;
            }
            result.value[i][j] %= Mod;
        }
    }
    return result;
}
matrix matrixPoweringMod(matrix a, long long k){
    matrix result;
    while(k != 0){
        if(k & 1)
            result = matrixMultiplication(result, a);
        a = matrixMultiplication(a, a);
        k /= 2;
    }
    return result;
}
long long k;
int main(int argc, char const *argv[])
{
    scanf("%d%lld", &n, &k);
    matrix original;
    for(int i = 0; i < n; i ++)
        for(int j = 0; j < n; j ++)
            scanf("%lld", &original.value[i][j]);
    matrix answer = matrixPoweringMod(original, k);
    for(int i = 0; i < n; i ++){
        for(int j = 0; j < n; j ++)
            printf("%lld ", answer.value[i][j]);
        printf("\n");
    }
    return 0;
}