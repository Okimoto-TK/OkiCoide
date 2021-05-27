#include <stdio.h>
using namespace std;
int n, m, b, mod;
int a[1007];
int f[1007][1007];
int main()
{
    scanf("%d%d%d%d", &n, &m, &b, &mod);
    for(int i = 1; i <= n; i++)
    {
        scanf("%d", &a[i]);
    }
    f[0][0] = 1;
    for(int i = 1; i <= n; i++)
    {
        for(int j = 1; j <= m; j++)
        {
            for(int k = a[i]; k <= b; k++)
            {
                (f[j][k] += f[j - 1][k - a[i]]) %= mod;
            }
        }
    }
    int ans = 0;
    for(int i = 0; i <= b; i++)
    {
        (ans += f[m][i]) %= mod;
    }
    printf("%d", ans);
    return 0;
}
