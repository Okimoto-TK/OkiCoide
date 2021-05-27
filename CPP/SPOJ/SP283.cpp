#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
int t;
int n, b;
long long u[4007];
long long f[4007][4007][2];
int main()
{
    scanf("%d", &t);
    while(t != 0)
    {
        scanf("%d%d", &n, &b);
        memset(f, -128/2, sizeof(f));
        long long ans = 0;
        for(int i = 1; i <= n; i++)
        {
            scanf("%lld", &u[i]);
        }
        for(int i = 1; i <= n; i++)
        {
            f[i][0][0] = 0;
        }
        f[1][1][1] = 0;
        for(int i = 2; i <= n; i++)
        {
            for(int j = 1; j <= b; j++)
            {
                f[i][j][0] = max(f[i - 1][j][0], f[i - 1][j][1]);
                f[i][j][1] = max(f[i - 1][j - 1][0], f[i - 1][j - 1][1] + u[i]);
            }
        }
        ans = max(f[n][b][0], f[n][b][1]);
        memset(f, -128 / 2, sizeof(f));
        for(int i = 1; i <= n; i++)
        {
            f[i][0][0] = 0;
        }
        f[1][1][1] = u[1];
        for(int i = 2; i <= n; i++)
        {
            for(int j = 1; j <= b; j++)
            {
                f[i][j][0] = max(f[i - 1][j][0], f[i - 1][j][1]);
                f[i][j][1] = max(f[i - 1][j - 1][0], f[i - 1][j - 1][1] + u[i]);
            }
        }
        ans = max(ans, f[n][b][1]);
        printf("%lld\n", ans);
        t--;
    }
    return 0;
}
