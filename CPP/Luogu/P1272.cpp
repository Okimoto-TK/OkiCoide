#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#define N 152
int n, p;
int siz[N];
std::vector<int> g[N];
int f[N][N];
void dfs(int u, int fa)
{
    siz[u] = 1;
    int len = g[u].size();
    for(int i = 0; i < len; i++)
    {
        int v = g[u][i];
        if(v == fa) continue;
        dfs(v, u);
        siz[u] += siz[v];
    }
    f[u][siz[u]] = 1;
    f[u][0] = 0;
}
void dp(int u, int fa)
{
    int len = g[u].size();
    for(int i = 0; i < len; i++)
    {
        int v = g[u][i];
        if(v == fa) continue;
        dp(v, u);
        for(int vl = siz[u] - 1; vl >= 0; vl--)
        {
            for(int k = 0; k <= vl; k++) f[u][vl] = std::min(f[u][vl], f[u][vl - k] + f[v][k]);
        }
    }
}
int main()
{
    memset(f, 0x3f, sizeof(f));
    scanf("%d%d", &n, &p);
    for(int i = 1; i < n; i++)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        g[u].push_back(v);
        g[v].push_back(u);
    }
    dfs(1, 0);
    f[1][siz[1]] = 0;
    dp(1, 0);
    int ans = 0x3f3f3f3f;
    for(int i = 1; i <= n; i++) ans = std::min(ans, f[i][siz[i] - p] + f[i][siz[i]]);
    printf("%d", ans);
    return 0;
}
