#include <stdio.h>
#include <algorithm>
using namespace std;
int m, n;
int a[11][11];
long long f[11][11];
int main()
{
    scanf("%d", &n);
    m = n;
    int x, y, w;
    scanf("%d%d%d", &x, &y, &w);
    while(x != 0 || y != 0 || w != 0)
    {
        a[x][y] = w;
        scanf("%d%d%d", &x, &y, &w);
    }
    for(int l = 2; l <= 2 * n; l++)
    {
        for(int i = l - 1; i >= 1; i--)
        {
            int j = l - i;
            for(int _i = l - 1; _i >= 1; _i--)
            {
                int _j = l - _i;
                f[i][_i] = max(max(f[i][_i], f[i - 1][_i]), max(f[i - 1][_i - 1], f[i][_i - 1]));
                f[i][_i] += a[i][j];
                if(i != _i)
                {
                    f[i][_i] += a[_i][_j];
                }
            }
        }
    }
    printf("%lld", f[m][m]);
}
