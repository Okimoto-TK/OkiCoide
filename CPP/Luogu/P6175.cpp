#include <stdio.h>
#include <string.h>
using namespace std;
int n, m;
int a[310][310];
int f[310][310];
const int INF = 200000000;
int ans = INF;
int getMin(int a, int b){
    return a < b ? a : b;
}
int main(int argc, char const *argv[])
{
    scanf("%d%d", &n, &m);
    for(int i = 0; i < 310; i ++)
        for(int j = 0; j < 310; j ++){
            a[i][j] = INF;
            f[i][j] = INF;
        }
    for(int i = 0; i <= n; i ++)
        a[i][i] = 0;
    for(int i = 0; i < m; i ++){
        int u, v, d;
        scanf("%d%d%d", &u, &v, &d);
        a[u][v] = getMin(a[u][v], d);
        a[v][u] = a[u][v];
        f[u][v] = a[u][v];
        f[v][u] = a[v][u];
    }
    for(int k = 1; k <= n; k ++){
        for(int i = 1; i < k; i ++){
            for(int j = i + 1; j < k; j ++){
                ans = getMin((long long)(f[i][j] + a[j][k] + a[k][i]), ans);
                //printf("%lld\n", (long long)(f[i][j] + a[j][k] + a[k][i]));
            }
        }
        for(int i = 1; i <= n; i ++){
            for(int j = 1; j <= n; j ++){
                f[i][j] = getMin(f[i][k] + f[k][j], f[i][j]);
            }
        }
    }
    if(ans == INF)
        printf("No solution.");
    else
        printf("%d", ans);
    return 0;
}