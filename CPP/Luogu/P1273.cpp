#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#define N 3002
int n, m;
int w[N];
std::vector<int> g[N];
int siz[N];
int f[N][N];
void dfs(int u)
{
    siz[u] = (u <= n && n - m + 1 <= u) ? 1 : 0;
    int len = g[u].size();
    for(int i = 0; i < len; i++)
    {
        int v = g[u][i];
        dfs(v);
        siz[u] += siz[v];
    }
}
void dp(int u)
{
    int len = g[u].size();
    f[u][0] = 0;
    if(len == 0) f[u][1] = 0;
    for(int i = 0; i < len; i++)
    {
        int v = g[u][i];
        dp(v);
        for(int j = siz[u]; j >= 1; j--)
        {
            for(int k = 1; k <= siz[v]; k++)
            {
                f[u][j] = std::max(f[u][j], f[u][j - k] + f[v][k]);
                //printf("%d %d: %d\n", u, j, f[u][j]);
            }
        }
    }
    for(int i = 1; i <= siz[u]; i++)
    {
        f[u][i] += w[u];
    }
}
int main()
{
    memset(f, ~0x3f, sizeof(f));
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= n - m; i++)
    {
        int k;
        scanf("%d", &k);
        for(int j = 1; j <= k; j++)
        {
            int a, c;
            scanf("%d%d", &a, &c);
            g[i].push_back(a);
            w[a] -= c;
        }
    }
    for(int i = n - m + 1; i <= n; i++)
    {
        int c;
        scanf("%d", &c);
        w[i] += c;
    }
    dfs(1);
    dp(1);
    int ans = 0;
    for(int i = m; i >= 0; i--)
    {
        if(f[1][i] >= 0)
        {
            ans = i;
            break;
        }
    }
    printf("%d", ans);
    return 0;
}
