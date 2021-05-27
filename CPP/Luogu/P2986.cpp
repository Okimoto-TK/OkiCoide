#include <cstdio>
#include <vector>
#include <algorithm>
#define MAXN 100007
int n;
long long sum;
long long c[MAXN];
long long f[MAXN];
std::vector<std::pair<int, int> > g[MAXN];
long long dfs1(int u, int fa)
{
    int len = g[u].size();
    long long res = 0;
    f[u] = c[u];
    for(int i = 0; i < len; i++)
    {
        int v = g[u][i].first;
        if(v == fa) continue;
        long long r = dfs1(v, u);
        res += r + f[v] * g[u][i].second;
        f[u] += f[v];
    }
    return res;
}
unsigned long long min;
unsigned long long ans;
void dfs2(int u, int fa)
{
    int len = g[u].size();
    for(int i = 0; i < len; i++)
    {
        int v = g[u][i].first;
        if(v == fa) continue;
        ans += (sum - 2 * f[v]) * g[u][i].second;
        min = std::min(min, ans);
        dfs2(v, u);
        ans -= (sum - 2 * f[v]) * g[u][i].second;
    }
}
int main()
{
    scanf("%d", &n);
    for(int i = 1; i <= n; i++)
    {
        scanf("%lld", &c[i]);
        sum += c[i];
    }
    for(int i = 1; i < n; i++)
    {
        int a, b, l;
        scanf("%d%d%d", &a, &b, &l);
        g[a].push_back(std::make_pair(b, l));
        g[b].push_back(std::make_pair(a, l));
    }
    min = ans = dfs1(1, 0);
    dfs2(1, 0);
    printf("%lld", min);
    return 0;
}
