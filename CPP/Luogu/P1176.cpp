#include <stdio.h>
#include <algorithm>
using namespace std;
int n, m;
int f[1007][1007];
bool b[1007][1007];
int main()
{
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= m; i++)
    {
        int x, y;
        scanf("%d%d", &x, &y);
        b[x][y] = true;
    }
    f[1][0] = 1;
    for(int i = 1; i <= n; i++)
    {
        for(int j = 1; j <= n; j++)
        {
            if(b[i][j])
            {
                continue;
            }
            f[i][j] = (f[i - 1][j] + f[i][j - 1]) % 100003;
        }
    }
    printf("%d", f[n][n]);
    return 0;
}
