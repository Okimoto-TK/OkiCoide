#include <stdio.h>
#include <string.h>
using namespace std;
int n, m;
int a[310][310];
int f[310][310];
int q[10007];
const int INF = 200000000;
int getMin(int a, int b){
    return a < b ? a : b;
}
int main(int argc, char const *argv[])
{
    scanf("%d%d", &n, &m);
    for(int i = 0; i < m; i ++)
        scanf("%d", &q[i]);
    for(int i = 0; i < 310; i ++)
        for(int j = 0; j < 310; j ++){
            f[i][j] = INF;
            a[i][j] = INF;
        }
    for(int i = 1; i <= n; i ++){
        for(int j = 1; j <= n; j ++){
            int d;
            scanf("%d", &d);
            a[i][j] = getMin(a[i][j], d);
            f[i][j] = a[i][j];
        }
    }
    for(int k = 1; k <= n; k ++){
        for(int i = 1; i <= n; i ++){
            for(int j = 1; j <= n; j ++){
                f[i][j] = getMin(f[i][k] + f[k][j], f[i][j]);
            }
        }
    }
    long long ans = 0;
    for(int i = 1; i < m; i ++){
        ans += f[q[i - 1]][q[i]];
    }
    if(ans == INF)
        printf("No solution.");
    else
        printf("%lld", ans);
    return 0;
}