#include <stdio.h>
#include <algorithm>
using namespace std;
int m, n;
int a[64][64];
int f[128][64][64];
int main()
{
    scanf("%d%d", &m, &n);
    for(int i = 1; i <= m; i++)
    {
        for(int j = 1; j <= n; j++)
        {
            scanf("%d", &a[i][j]);
        }
    }
    for(int l = 3; l <= m + n; l++)
    {
        for(int i = max(1, l - n); l - i >= 1 && i <= m; i++)
        {
            int j = l - i;
            for(int _i = max(1, l - n); l - _i >= 1 && _i <= m; _i++)
            {
                if(i == _i)
                {
                    continue;
                }
                int _j = l - _i;
                if(_j != 1 && i != 1)
                {
                    f[l][i][_i] = max(f[l][i][_i], f[l - 1][i - 1][_i] + a[i][j] + a[_i][_j]);
                }
                if(_j != 1 && j != 1)
                {
                    f[l][i][_i] = max(f[l][i][_i], f[l - 1][i][_i] + a[i][j] + a[_i][_j]);
                }
                if(_i != 1 && j != 1)
                {
                    f[l][i][_i] = max(f[l][i][_i], f[l - 1][i][_i - 1] + a[i][j] + a[_i][_j]);
                }
                if(_i != 1 && i != 1)
                {
                    f[l][i][_i] = max(f[l][i][_i], f[l - 1][i - 1][_i - 1] + a[i][j] + a[_i][_j]);
                }
            }
        }
    }
    printf("%d", f[n + m - 1][m][m - 1]);
}
