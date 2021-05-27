#include <cstdio>
#include <algorithm>
#define N 102
int n;
int s[N];
int a[N];
long long f[N][N][N];
int main()
{
    scanf("%d", &n);
    for(int i = 1; i <= n; i++) scanf("%1d", &s[i]);
    for(int i = 1; i <= n; i++)
    {
        scanf("%d", &a[i]);
    }
    for(int i = n; i >= 1; i--)
    {
        for(int j = i; j <= n; j++)
        {
            for(int x = 0; x < n; x++)
            {
                f[i][j][x] = f[i][j - 1][0] + a[x + 1];
                for(int k = i; k < j; k++)
                {
                    if(s[j] == s[k]) f[i][j][x] = std::max(f[i][j][x], f[i][k][x + 1] + f[k + 1][j - 1][0]);
                }
            }
        }
    }
    printf("%lld", f[1][n][0]);
    return 0;
}
