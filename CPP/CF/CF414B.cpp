#include <stdio.h>
using namespace std;
int n, k;
const int p = 1000000007;
int a[2007];
int f[2007][2007];
int main()
{
    scanf("%d%d", &n, &k);
    for(int i = 1; i <= n; i++)
    {
        f[1][i] = 1;
    }
    for(int i = 2; i <= k; i++)
    {
        for(int j = 1; j <= n; j++)
        {
            for(int x = j; x <= n; x += j)
            {
                (f[i][x] += f[i - 1][j]) %= p;
            }
        }
    }
    int ans = 0;
    for(int i = 1; i <= n; i++)
    {
        (ans += f[k][i]) %= p;
    }
    printf("%d", ans);
    return 0;
}
