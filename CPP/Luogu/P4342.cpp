#include <stdio.h>
#include <algorithm>
#include <string.h>
#include <queue>
using namespace std;
int n;
int a[128];
int f[128][128];
int g[128][128];
bool op[128];
int main()
{
    memset(f, -128 / 2, sizeof(f));
    memset(g, 0x3f, sizeof(g));
    scanf("%d", &n);
    for(int i = 1; i <= n; i++)
    {
        char buf[2];
        scanf("%s%d", buf, &a[i]);
        f[i][i] = a[i];
        g[i][i] = a[i];
        f[i + n][i + n] = a[i];
        g[i + n][i + n] = a[i];
        op[i - 1] = buf[0] == 't';
        op[i + n - 1] = op[i - 1];
    }
    for(int l = 2; l <= n; l++)
    {
        for(int i = 1; i + l - 1 <= 2 * n; i++)
        {
            int j = i + l - 1;
            for(int k = i; k < j; k++)
            {
                if(op[k])
                {
                    f[i][j] = max(f[i][j], f[i][k] + f[k + 1][j]);
                    g[i][j] = min(g[i][j], g[i][k] + g[k + 1][j]);
                }
                else
                {
                    f[i][j] = max(f[i][j], f[i][k] * f[k + 1][j]);
                    f[i][j] = max(f[i][j], f[i][k] * g[k + 1][j]);
                    f[i][j] = max(f[i][j], g[i][k] * g[k + 1][j]);
                    f[i][j] = max(f[i][j], g[i][k] * f[k + 1][j]);
                    g[i][j] = min(g[i][j], f[i][k] * f[k + 1][j]);
                    g[i][j] = min(g[i][j], f[i][k] * g[k + 1][j]);
                    g[i][j] = min(g[i][j], g[i][k] * g[k + 1][j]);
                    g[i][j] = min(g[i][j], g[i][k] * f[k + 1][j]);
                }
            }
        }
    }
    int ans = -0x3f3f3f3f;
    queue <int> q;
    for(int i = 1; i <= n; i++)
    {
        if(f[i][i + n - 1] > ans)
        {
            ans = f[i][i + n - 1];
            while(!q.empty())
            {
                q.pop();
            }
            q.push(i);
        }
        else if(f[i][i + n - 1] == ans)
        {
            q.push(i);
        }
    }
    printf("%d\n", ans);
    while(!q.empty())
    {
        printf("%d ", q.front());
        q.pop();
    }
    return 0;
}
