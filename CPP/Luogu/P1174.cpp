#include <cstdio>
#include <algorithm>
int n, m, k;
int a[202][202];
int sum1[202][202];
int sum2[202][202];
int c[202][202];
int f[202][202][2];
int main()
{
    scanf("%d%d%d", &n, &m, &k);
    for(int i = 1; i <= n; i++)
    {
        for(int j = 1; j <= m; j++)
        {
            char buf[2];
            scanf("%d%1s", &a[i][j], buf);
            c[i][j] = ((buf[0] == 'Y') ? 1 : 0);
        }
    }
    for(int j = 1; j <= m; j++)
    {
        int cnt = 0;
        for(int i = n; i >= 1; i--)
        {
            if(c[i][j] == 1)
            {
                sum1[j][cnt] += a[i][j];
            }
            else
            {
                cnt++;
                sum2[j][cnt] = sum1[j][cnt - 1] + a[i][j];
                sum1[j][cnt] = sum1[j][cnt - 1] + a[i][j];
            }
        }
    }
    for(int i = 1; i <= m; i++)
    {
        for(int x = 0; x <= k; x++)
        {
            for(int y = 0; y <= x && y <= n; y++)
            {
                f[i][x][1] = std::max(f[i][x][1], f[i - 1][x - y][1] + sum1[i][y]);
                if(y != 0) f[i][x][0] = std::max(f[i][x][0], f[i - 1][x - y][1] + sum2[i][y]);
                if(x - y > 0) f[i][x][0] = std::max(f[i][x][0], f[i - 1][x - y][0] + sum1[i][y]);
            }
        }
    }
    printf("%d", f[m][k][0]);
    return 0;
}
