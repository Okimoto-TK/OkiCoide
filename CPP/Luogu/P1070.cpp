#include <stdio.h>
#include <algorithm>
#include <string.h>
using namespace std;
int n, m, p;
int a[1007][1007];
int b[1007];
int f[1007];
int main()
{
    memset(f, -128 / 2, sizeof(f));
    f[0] = 0;
    scanf("%d%d%d", &n, &m, &p);
    for(int i = 1; i <= n; i++)
    {
        for(int j = 1; j <= m; j++)
        {
            scanf("%d", &a[i][j]);
        }
    }
    for(int i = 1; i <= n; i++)
    {
        scanf("%d", &b[i]);
    }
    for(int t = 1; t <= m; t++)
    {
        for(int i = 1; i <= n; i++)
        {
            int x = i - 1 == 0 ? n : i - 1;
            int c = a[x][t];
            for(int j = 1; j <= p; j++)
            {
                if(t - j < 0)
                {
                    break;
                }
                f[t] = max(f[t], f[t - j] + c - b[x]);
                x--;
                x = x == 0 ? n : x;
                c += a[x][t - j];
            }
        }
    }
    printf("%d", f[m]);
    return 0;
}
