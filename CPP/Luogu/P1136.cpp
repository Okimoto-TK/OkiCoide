#include <cstdio>
#include <cstring>
#include <algorithm>
#define N 502
int n, m;
char a[N];
int f[501][101][101][2];
int main()
{
    scanf("%d%d", &n, &m);
    scanf("%s", a + 1);
    memset(f, 128, sizeof(f));
    f[0][0][0][0] = 0;
    for(int i = 1; i <= n; i++)
    {
        for(int j = 0; j <= m; j++) // swap of j
        {
            for(int k = 0; k <= m; k++) // swap of z
            {
                if(a[i] == 'j') // j
                {
                    f[i][j][k][1] = std::max(f[i - 1][j][k][0], f[i - 1][j][k][1]);
                    if(j > 0) f[i][j][k][0] = std::max(f[i - 1][j - 1][k][1] + 1, f[i - 1][j - 1][k][0]);
                }
                else // z
                {
                    f[i][j][k][0] = std::max(f[i - 1][j][k][1] + 1, f[i - 1][j][k][0]);
                    if(k > 0) f[i][j][k][1] = std::max(f[i - 1][j][k - 1][1], f[i - 1][j][k - 1][0]);
                }
            }
        }
    }
    int ans = 0;
    for(int i = 0; i <= m; i++)
    {
        ans = std::max(ans, std::max(f[n][i][i][0], f[n][i][i][1]));
    }
    printf("%d", ans);
    return 0;
}
