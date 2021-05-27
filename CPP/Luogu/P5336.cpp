#include <stdio.h>
#include <string.h>
#include <algorithm>
#define N 53
using namespace std;
int n, m, a, b;
int w[N];
int v[N];
int f[N][N][N][N];
int g[N][N];
int main()
{
    scanf("%d", &n);
    scanf("%d%d", &a, &b);
    for(int i = 1; i <= n; i++)
    {
        scanf("%d", &w[i]);
        v[i] = w[i];
    }
    sort(v + 1, v + 1 + n);
    int m = unique(v + 1, v + 1 + n) - v - 1;
    memset(f, 0x3f, sizeof(f));
    memset(g, 0x3f, sizeof(g));
    for(int i = 1; i <= n; i++)
    {
        w[i] = lower_bound(v + 1, v + 1 + m, w[i]) - v;
        f[i][i][w[i]][w[i]] = 0;
        g[i][i] = a;
    }
    for(int l = 1; l <= n; l++)
    {
        for(int i = 1; i + l - 1 <= n; i++)
        {
            int j = i + l - 1;
            for(int x = 1; x <= m; x++)
            {
                for(int y = 1; y <= x; y++)
                {
                    f[i][j][max(x, w[j])][min(y, w[j])] = min(f[i][j][max(x, w[j])][min(y, w[j])], f[i][j - 1][x][y]);
                    for(int k = i; k < j; k++)
                    {
                        f[i][j][x][y] = min(f[i][j][x][y], f[i][k][x][y] + g[k + 1][j]);
                    }
                }
            }
            for(int x = 1; x <= m; x++)
            {
                for(int y = 1; y <= x; y++)
                {
                    g[i][j] = min(g[i][j], f[i][j][x][y] + a + b * (v[x] - v[y]) * (v[x] - v[y]));
                }
            }
        }
    }
    printf("%d", g[1][n]);
    return 0;
}
