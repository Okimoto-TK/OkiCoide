#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
#define N 202
int n;
int a[N];
int f[N][N][N];
void run(int cse)
{
    scanf("%d", &n);
    for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
    for(int i = n; i >= 1; i--)
    {
        for(int j = i; j <= n; j++)
        {
            for(int x = 0; x < n; x++)
            {
                f[i][j][x] = f[i][j - 1][0] + pow(x + 1, 2);
                for(int k = i; k < j; k++)
                {
                    if(a[j] == a[k]) f[i][j][x] = std::max(f[i][j][x], f[i][k][x + 1] + f[k + 1][j - 1][0]);
                }
            }
        }
    }
    printf("Case %d: %d\n", cse, f[1][n][0]);
}
int main()
{
    int t;
    scanf("%d", &t);
    for(int i = 1; i <= t; i++) run(i);
    return 0;
}
