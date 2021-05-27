#include <cstdio>
#include <vector>
#include <algorithm>
#define N 100007
int n, m;
struct edge
{
    int i;
    int v;
    edge(int x, int y)
    {
        v = x;
        i = y;
    }
};
std::vector<edge> g[N];
int lnk[N];
int siz[N];
int son[N];
int dep[N];
int spr[N];
void dfs1(int u, int fa)
{
    siz[u] = 1;
    dep[u] = dep[fa] + 1;
    spr[u] = fa;
    int len = g[u].size();
    for(int i = 0; i < len; i++)
    {
        int v = g[u][i].v;
        int id = g[u][i].i;
        if(v == fa) continue;
        lnk[id] = v;
        dfs1(v, u);
        siz[u] += siz[v];
        if(siz[v] > siz[son[u]]) son[u] = v;
    }
}
int seg[N];
int rpr[N];
int top[N];
void dfs2(int u)
{
    if(son[u])
    {
        int v = son[u];
        seg[v] = ++seg[0];
        rpr[seg[0]] = v;
        top[v] = top[u];
        dfs2(v);
    }
    int len = g[u].size();
    for(int i = 0; i < len; i++)
    {
        int v = g[u][i].v;
        if(top[v] != 0) continue;
        seg[v] = ++seg[0];
        rpr[seg[0]] = v;
        top[v] = v;
        dfs2(v);
    }
}
int t[N << 2];
void change(int k, int l, int r, int x, int v)
{
    if(l == r)
    {
        t[k] = v;
        return;
    }
    int mid = (l + r) >> 1;
    if(x <= mid) change(k << 1, l, mid, x, v);
    else change(k << 1 | 1, mid + 1, r, x, v);
    t[k] = t[k << 1] + t[k << 1 | 1];
}
int query(int k, int l, int r, int x, int y)
{
    if(x <= l && r <= y) return t[k];
    int mid = (l + r) >> 1;
    int res = 0;
    if(x <= mid) res += query(k << 1, l, mid, x, y);
    if(y > mid) res += query(k << 1 | 1, mid + 1, r, x, y);
    return res;
}
std::pair<int, int> ask(int x, int y)
{
    int fx = top[x];
    int fy = top[y];
    int res = 0;
    int all = 0;
    while(fx != fy)
    {
        if(dep[fx] < dep[fy])
        {
            std::swap(fx, fy);
            std::swap(x, y);
        }
        res += query(1, 1, seg[0], seg[fx], seg[x]);
        all += seg[x] - seg[fx] + 1;
        x = spr[fx];
        fx = top[x];
    }
    if(x == y)
    {
        return std::make_pair(res, all);
    }
    else if(dep[x] > dep[y]) std::swap(x, y);
    res += query(1, 1, seg[0], seg[x] + 1, seg[y]);
    all += seg[y] - seg[x];
    return std::make_pair(res, all);
}
int main()
{
    scanf("%d", &n);
    for(int i = 1; i < n; i++)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        g[u].push_back(edge(v, i));
        g[v].push_back(edge(u, i));
    }
    dfs1(1, 0);
    seg[1] = seg[0] = rpr[1] = top[1] = 1;
    dfs2(1);
    scanf("%d", &m);
    for(int i = 1; i <= m; i++)
    {
        int opt;
        scanf("%d", &opt);
        if(opt == 1)
        {
            int u;
            scanf("%d", &u);
            change(1, 1, seg[0], seg[lnk[u]], 0);
        }
        else if(opt == 2)
        {
            int u;
            scanf("%d", &u);
            change(1, 1, seg[0], seg[lnk[u]], 1);
        }
        else
        {
            int u, v;
            scanf("%d%d", &u, &v);
            std::pair<int, int> r = ask(u, v);
            if(r.first != 0) printf("-1\n");
            else printf("%d\n", r.second);
        }
    }
    return 0;
}
