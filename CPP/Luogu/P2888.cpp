#include <stdio.h>
using namespace std;
int n, m, t;
const int INF = 100000000;
int a[307][307];
int f[307][307];
int getMin(int a, int b){
    return a < b ? a : b;
}
int getMax(int a, int b){
    return a > b ? a : b;
}
int main(int argc, char const *argv[])
{
    scanf("%d%d%d", &n, &m, &t);
    for(int i = 0; i < 307; i ++){
        for(int j = 0; j < 307; j ++){
            a[i][j] = INF;
            f[i][j] = INF;
        }
        a[i][i] = 0;
    }
    for(int i = 0; i < m; i ++){
        int s, e, h;
        scanf("%d%d%d", &s, &e, &h);
        a[s][e] = getMin(a[s][e], h);
        f[s][e] = a[s][e];
    }
    for(int k = 1; k <= n; k ++){
        for(int i = 1; i <= n; i ++){
            for(int j = 1; j <= n; j ++){
                f[i][j] = getMin(f[i][j], getMax(f[i][k], f[k][j]));
            }
        }
    }
    for(int i = 0; i < t; i ++){
        int u, v;
        scanf("%d%d", &u, &v);
        printf("%d\n", f[u][v] == INF ? -1 : f[u][v]);
    }
    return 0;
}