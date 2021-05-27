#include <stdio.h>
using namespace std;
const int INF = 100000000;
int getMin(int a, int b){
    return a < b ? a : b;
}
int q[1007];
int d[1007][1007];
int a[1007][1007];
int p, f, c;
int min = INF;
int ans;
int main(int argc, char const *argv[])
{
    scanf("%d%d%d", &p, &f, &c);
    for(int i = 0; i < f; i ++)
        scanf("%d", &q[i]);
    for(int i = 0; i < 1007; i ++)
        for(int j = 0; j < 1007; j ++){
            a[i][j] = INF;
            d[i][j] = INF;
        }
    for(int i = 0; i < 1007; i ++){
        a[i][i] = 0;
        d[i][i] = 0;
    }
    for(int i = 0; i < c; i ++){
        int u, v, t;
        scanf("%d%d%d", &u, &v, &t);
        a[u][v] = getMin(a[u][v], t);
        d[u][v] = a[u][v];
        a[v][u] = a[u][v];
        d[v][u] = a[v][u];
    }
    for(int k = 1; k <= p; k ++){
        for(int i = 1; i <= p; i ++){
            for(int j = 1; j <= p; j ++){
                d[i][j] = getMin(d[i][j], d[i][k] + d[k][j]);
            }
        }
    }
    for(int i = 1; i <= p; i ++){
        int cnt = 0;
        for(int j = 0; j < f; j ++)
            cnt += d[i][q[j]];
        if(cnt < min){
            min = cnt;
            ans = i;
        }
    }
    printf("%d", ans);
    return 0;
}