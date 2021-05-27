#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
int n, s;
int map[307][307];
int f[307][307];
int main()
{
    memset(f, 0x3f, sizeof(f));
    scanf("%d%d", &n, &s);
    for(int i = 1; i < n; i++)
    {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        f[u][v] = w;
        f[v][u] = w;
    }
    for(int i = 1; i <= n; i++)
    {
        f[i][i] = 0;
        for(int j = 1; j <= n; j++)
        {
            if(i == j)
            {
                continue;
            }
            for(int k = 1; k <= n; k++)
            {
                if(i == k || j == k)
                {
                    continue;
                }
                f[j][k] = min(f[j][k], f[j][i] + f[i][k]);
            }
        }
    }
    int ans = 0x3f3f3f3f;
    for(int i = 1; i <= n; i++)
    {
        for(int j = 1; j <= n; j++)
        {
            if(i == j || f[i][j] <= s)
            {
                f[i][i] = 0;
                int buf = 0;
                for(int k = 1; k <= n; k++)
                {
                    if(i == k || j == k)
                    {
                        continue;
                    }
                    buf = max((f[k][i] + f[k][j] - f[i][j]) / 2, buf);
                }
                ans = min(ans, buf);
            }
        }
    }
    printf("%d", ans);
    return 0;
}
