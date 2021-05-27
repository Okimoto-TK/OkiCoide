#include <stdio.h>
#include <algorithm>
using namespace std;
int n, m;
int a[1507][1507];
int f[1507][1507][2];
int main()
{
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= n; i++)
    {
        for(int j = 1; j <= m; j++)
        {
            scanf("%d", &a[i][j]);
        }
    }
    int ans = 0;
    for(int i = 1; i <= n; i++)
    {
        for(int j = 1; j <= m; j++)
        {
            f[i][j][a[i][j]] = min(f[i][j - 1][1 - a[i][j]], min(f[i - 1][j][1 - a[i][j]], f[i - 1][j - 1][a[i][j]])) + 1;
            ans = max(ans, f[i][j][a[i][j]]);
        }
    }
    printf("%d", ans);
    return 0;
}
