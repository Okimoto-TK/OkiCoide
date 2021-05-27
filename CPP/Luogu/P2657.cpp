#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
int a, b;
int g[16];
int f[16][10];
int dp(int x)
{
    memset(g, 0, sizeof(g));
    int len = 0;
    int res = 0;
    while(x)
    {
        g[++len] = x % 10;
        x /= 10;
    }
    for(int i = 1; i <= len - 1; i++)
    {
        for(int j = 1; j <= 9; j++)
        {
            res += f[i][j];
        }
    }
    for(int i = 1; i < g[len]; i++)
    {
        res += f[len][i];
    }
    for(int i = len - 1; i >= 1; i--)
    {
        for(int j = 0; j <= g[i] - 1; j++)
        {
            if(abs(j - g[i + 1]) >= 2)
            {
                res += f[i][j];
            }
        }
        if(abs(g[i + 1] - g[i]) < 2)
        {
            break;
        }
    }
    return res;
}
int main()
{
    for(int i = 0; i < 10; i++)
    {
        f[1][i] = 1;
    }
    for(int k = 2; k <= 10; k++)
    {
        for(int i = 0; i < 10; i++)
        {
            for(int j = 0; j <= i - 2; j++)
            {
                f[k][i] += f[k - 1][j];
            }
            for(int j = 9; j >= i + 2; j--)
            {
                f[k][i] += f[k - 1][j];
            }
        }
    }
    scanf("%d%d", &a, &b);
    printf("%d", dp(b + 1) - dp(a));
    return 0;
}
