#include <cstdio>
#include <vector>
#include <algorithm>
#define N 10007
#define M 50007
int n, m, q;
struct Edge
{
    int u, v, w;
    Edge() { u = v = w = 0; }
} edge[M];
bool cmp(Edge a, Edge b)
{
    return a.w > b.w;
}
int a[N];
int find(int x)
{
    if(x == a[x]) return x;
    return a[x] = find(a[x]);
}
std::vector<std::pair<int, int> > g[N];
int dep[N];
int siz[N];
int spr[N];
int son[N];
int val[N];
void dfs1(int u, int fa)
{
    dep[u] = dep[fa] + 1;
    spr[u] = fa;
    siz[u] = 1;
    int len = g[u].size();
    for(int i = 0; i < len; i++)
    {
        int v = g[u][i].first;
        if(v == fa) continue;
        val[v] = g[u][i].second;
        dfs1(v, u);
        siz[u] += siz[v];
        if(siz[son[u]] < siz[v]) son[u] = v;
    }
}
int top[N];
void dfs2(int u)
{
    if(son[u])
    {
        top[son[u]] = top[u];
        dfs2(son[u]);
    }
    int len = g[u].size();
    for(int i = 0; i < len; i++)
    {
        int v = g[u][i].first;
        if(top[v] != 0) continue;
        top[v] = v;
        dfs2(v);
    }
}
int ask(int x, int y)
{
    int fx = top[x];
    int fy = top[y];
    int min = 0x3f3f3f3f;
    while(fx != fy)
    {
        if(dep[fx] < dep[fy])
        {
            std::swap(x, y);
            std::swap(fx, fy);
        }
        while(x != fx)
        {
            min = std::min(val[x], min);
            x = spr[x];          
        }
        min = std::min(val[x], min);
        x = spr[fx];
        fx = top[x];
    }
    if(x == y) return min;
    if(dep[x] > dep[y]) std::swap(x, y);
    while(y != x)
    {
        min = std::min(val[y], min);
        y = spr[y];
    }
    return min;
}
int main()
{
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= n; i++) a[i] = i;
    for(int i = 1; i <= m; i++)
    {
        int x, y, z;
        scanf("%d%d%d", &x, &y, &z);
        edge[i].u = x;
        edge[i].v = y;
        edge[i].w = z;
    }
    std::sort(edge + 1, edge + 1 + m, cmp);
    for(int i = 1; i <= m; i++)
    {
        int u = edge[i].u;
        int v = edge[i].v;
        int w = edge[i].w;
        if(find(u) == find(v)) continue;
        g[u].push_back(std::make_pair(v, w));
        g[v].push_back(std::make_pair(u, w));
        a[find(u)] = find(v);
    }
    dfs1(1, 0);
    top[1] = 1;
    dfs2(1);
    scanf("%d", &q);
    for(int i = 1; i <= q; i++)
    {
        int x, y;
        scanf("%d%d", &x, &y);
        if(find(x) != find(y)) printf("-1\n");
        else printf("%d\n", ask(x, y));
    }
    return 0;
}
