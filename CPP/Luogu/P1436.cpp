#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
#define N 8
#define _N 10
int n;
int a[_N][_N];
long long f[16][_N][_N][_N][_N];
int sum[_N][_N];
int main()
{
    scanf("%d", &n);
    for(int i = 1; i <= N; i++)
    {
        for(int j = 1; j <= N; j++) scanf("%d", &a[i][j]);
    }
    for(int i = 1; i <= N; i++)
    {
        for(int j = 1; j <= N; j++) sum[i][j] = sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1] + a[i][j];
    }
    for(int sx = 1; sx <= N; sx++)
    {
        for(int sy = 1; sy <= N; sy++)
        {
            for(int ex = sx; ex <= N; ex++)
            {
                for(int ey = sy; ey <= N; ey++) f[0][sx][sy][ex][ey] = pow(sum[ex][ey] - sum[sx - 1][ey] - sum[ex][sy - 1] + sum[sx - 1][sy - 1], 2);
            }
        }
    }
    for(int k = 1; k < n; k++)
    {
        for(int sx = 1; sx <= N; sx++)
        {
            for(int sy = 1; sy <= N; sy++)
            {
                for(int ex = sx; ex <= N; ex++)
                {
                    for(int ey = sy; ey <= N; ey++)
                    {
                        f[k][sx][sy][ex][ey] = 0x3f3f3f3f3f3f3f3f;
                        for(int x = sx; x < ex; x++) f[k][sx][sy][ex][ey] = std::min(f[k][sx][sy][ex][ey], std::min(f[k - 1][sx][sy][x][ey] + f[0][x + 1][sy][ex][ey], f[0][sx][sy][x][ey] + f[k - 1][x + 1][sy][ex][ey]));
                        for(int y = sy; y < ey; y++) f[k][sx][sy][ex][ey] = std::min(f[k][sx][sy][ex][ey], std::min(f[k - 1][sx][sy][ex][y] + f[0][sx][y + 1][ex][ey], f[0][sx][sy][ex][y] + f[k - 1][sx][y + 1][ex][ey]));
                    }
                }
            }
        }
    }
    printf("%lld", f[n - 1][1][1][N][N]);
    return 0;
}
