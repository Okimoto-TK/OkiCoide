#include <stdio.h>
#include <algorithm>
using namespace std;
int n, m, k;
int a[1007][1007];
int f[802][802][16][2];
const int mod = 1000000007;
int main()
{
    scanf("%d%d%d", &n, &m, &k);
    for(int i = 1; i <= n; i++)
    {
        for(int j = 1; j <= m; j++)
        {
            scanf("%d", &a[i][j]);
        }
    }
    for(int i = 1; i <= n; i++)
    {
        for(int j = 1; j <= m; j++)
        {
            f[i][j][a[i][j]][0] = 1;
        }
    }
    for(int i = 1; i <= n; i++)
    {
        for(int j = 1; j <= m; j++)
        {
            for(int _k = 0; _k <= k; _k++)
            {
                if(i != 1)
                {
                    (f[i][j][_k][0] += f[i - 1][j][(_k - a[i][j] + k + 1) % (k + 1)][1]) %= mod;
                    (f[i][j][_k][1] += f[i - 1][j][(_k + a[i][j]) % (k + 1)][0]) %= mod;
                }
                if(j != 1)
                {
                    (f[i][j][_k][0] += f[i][j - 1][(_k - a[i][j] + k + 1) % (k + 1)][1]) %= mod;
                    (f[i][j][_k][1] += f[i][j - 1][(_k + a[i][j]) % (k + 1)][0]) %= mod;
                }
            }
        }
    }
    int ans = 0;
    for(int i = 1; i <= n; i++)
    {
        for(int j = 1; j <= m; j++)
        {
            (ans += f[i][j][0][1]) %= mod;
        }
    }
    printf("%d", ans);
    return 0;
}
