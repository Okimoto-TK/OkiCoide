#include <stdio.h>
using namespace std;
int n, m;
int a[1007][1007];
long long f[1007][1007][2];
void init(){
    for(int i = 0; i < 1007; i ++){
        for(int j = 0; j < 1007; j ++){
            f[i][j][0] = -20000000000L;
            f[i][j][1] = f[i][j][0];
        }
    }
}
inline long long getMax(long long a, long long b){
    return a > b ? a : b;
}
int main(int argc, char const *argv[])
{
    init();
    //freopen("number.in", "r", stdin);
    //freopen("number.out", "w", stdout);
    scanf("%d%d", &n, &m);
    for(register int i = 0; i < n; i ++){
        for(register int j = 0; j < m; j ++){
            scanf("%d", &a[i][j]);
        }
    }
    f[0][0][0] = a[0][0];
    f[0][0][1] = a[0][0];
    for(register int i = 1; i < n; i ++){
        f[i][0][0] = f[i - 1][0][0] + a[i][0];
    }
    for(register int i = 1; i < m; i ++){
        f[0][i][0] = f[0][i - 1][1] + a[0][i];
        for(register int j = 1; j < n; j ++){
            f[j][i][0] = getMax(getMax(f[j][i - 1][0], f[j][i - 1][1]), f[j - 1][i][0]) + a[j][i];
        }
        f[n - 1][i][1] = f[n - 1][i - 1][0] + a[n - 1][i];
        for(register int j = n - 2; j >= 0; j --){
            f[j][i][1] = getMax(getMax(f[j][i - 1][0], f[j][i - 1][1]), f[j + 1][i][1]) + a[j][i];
        }
    }
    printf("%lld", getMax(f[n - 1][m - 1][0], f[n - 1][m - 1][1]));
    return 0;
}
