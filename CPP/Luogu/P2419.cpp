#include <stdio.h>
using namespace std;
const int INF = 100000000;
int n, m;
int ans;
int a1[107][107];
int a2[107][107];
int f1[107][107];
int f2[107][107];
int getMin(int a, int b){
    return a < b ? a : b;
}
int main(int argc, char const *argv[])
{
    scanf("%d%d", &n, &m);
    for(int i = 0; i < 107; i ++)
        for(int j = 0; j < 107; j ++){
            a1[i][j] = INF;
            a2[i][j] = INF;
            f1[i][j] = INF;
            f2[i][j] = INF;
        }
    for(int i = 0; i < 107; i ++){
        a1[i][i] = 0;
        a2[i][i] = 0;
    }
    for(int i = 0; i < m; i ++){
        int u, v;
        scanf("%d%d", &u, &v);
        a1[u][v] = getMin(0, a1[u][v]);
        a2[v][u] = getMin(0, a2[v][u]);
        f1[u][v] = a1[u][v];
        f2[v][u] = a2[v][u];
    }
    for(int k = 1; k <= n; k ++){
        for(int i = 1; i <= n; i ++){
            for(int j = 1; j <= n; j ++){
                f1[i][j] = getMin(f1[i][j], f1[i][k] + f1[k][j]);
                f2[i][j] = getMin(f2[i][j], f2[i][k] + f2[k][j]);
            }
        }
    }
    for(int i = 1; i <= n; i ++){
        bool have = true;
        for(int j = 1; j <= n; j ++){
            if(i == j)
                continue;
            if(f1[i][j] == 0 || f2[i][j] == 0)
                continue;
            else{
                have = false;
                break;
            }
        }
        if(have)
            ans ++;
    }
    printf("%d\n", ans);
    return 0;
}