#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <bitset>
using namespace std;
int n, m;
int dis[16][16];
long long f[16][5007];
int g[5007][5007];
int bit(int x)
{
    int r = 0;
    while(x)
    {
        r++;
        n &= n - 1;
    }
    return r;
}
int main()
{
    memset(f, 0x3f, sizeof(f));
    memset(dis, 0x3f, sizeof(dis));
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= m; i++)
    {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        dis[u][v] = min(dis[u][v], w);
        dis[v][u] = min(dis[v][u], w);
    }
    for(int i = 0; i < 1 << n; i++)
    {
        for(int j = i; j; j = (j - 1) & i)
        {
            int t = i ^ j;
            bool b = true;
            for(int k = n; k >= 1; k--)
            {
                if(t >= (1 << (k - 1)))
                {
                    int tmp = 0x3f3f3f3f;
                    for(int u = 1; u <= n; u++)
                    {
                        if((1 << (u - 1) & j) == (1 << (u - 1)))
                        {
                            tmp = min(tmp, dis[u][k]);
                        }
                    }
                    if(tmp == 0x3f3f3f3f)
                    {
                        b = false;
                        break;
                    }
                    g[j][i] += tmp;
                    t -= (1 << (k - 1));
                }
            }
            if(!b)
            {
                g[j][i] = 0x3f3f3f3f;
            }
        }
    }
    for(int i = 1; i <= n; i++)
    {
        f[1][1 << (i - 1)] = 0;
    }
    for(int i = 2; i <= n; i++)
    {
        for(int b = 0; b < 1 << n; b++)
        {
            for(int _b = b; _b; _b = (_b - 1) & b)
            {
                if(g[_b][b] != 0x3f3f3f3f)
                {
                    f[i][b] = min(f[i][b], f[i - 1][_b] + (i - 1) * g[_b][b]);
                }
            }
        }
    }
    long long ans = 0x3f3f3f3f3f3f3f3f;
    for(int i = 1; i <= n; i++)
    {
        ans = min(ans, f[i][(1 << n) - 1]);
    }
    printf("%lld", ans);
    return 0;
}
