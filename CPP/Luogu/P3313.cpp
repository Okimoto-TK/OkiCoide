#include <cstdio>
#include <vector>
#include <algorithm>
#define N 100005
int n, q, pool;
int w[N];
int c[N];
std::vector<int> g[N];
int dep[N];
int siz[N];
int son[N];
int spr[N];
void dfs1(int u, int fa)
{
    spr[u] = fa;
    dep[u] = dep[fa] + 1;
    siz[u] = 1;
    int len = g[u].size();
    for(int i = 0; i < len; i++)
    {
        int v = g[u][i];
        if(v == fa) continue;
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
    if(son[u] != 0)
    {
        int v = son[u];
        seg[v] = ++seg[0];
        rpr[seg[v]] = v;
        top[v] = top[u];
        dfs2(v);
    }
    int len = g[u].size();
    for(int i = 0; i < len; i++)
    {
        int v = g[u][i];
        if(top[v] != 0) continue;
        seg[v] = ++seg[0];
        rpr[seg[v]] = v;
        top[v] = v;
        dfs2(v);
    }
}
int rt[N];
struct Node
{
    int lch;
    int rch;
    int sum;
    int max;
    Node() { lch = rch = sum = max = 0; }
} t[10000000];
void update(int &k, int l, int r, int x, int v)
{
    if(k == 0) k = ++pool;
    if(l == r)
    {
        t[k].sum = t[k].max = v;
        return;
    }
    int mid = (l + r) >> 1;
    if(x <= mid) update(t[k].lch, l, mid, x, v);
    else update(t[k].rch, mid + 1, r, x, v);
    t[k].sum = t[t[k].lch].sum + t[t[k].rch].sum;
    t[k].max = std::max(t[t[k].lch].max, t[t[k].rch].max);
}
int querySum(int k, int l, int r, int x, int y)
{
    if(k == 0) return 0;
    if(x <= l && r <= y)
    {
        return t[k].sum;
    }
    int mid = (l + r) >> 1;
    int res = 0;
    if(x <= mid) res += querySum(t[k].lch, l, mid, x, y);
    if(y > mid) res += querySum(t[k].rch, mid + 1, r, x, y);
    return res;
}
int askSum(int x, int y, int c)
{
    int fx = top[x];
    int fy = top[y];
    int res = 0;
    while(fx != fy)
    {
        if(dep[fx] < dep[fy])
        {
            std::swap(fx, fy);
            std::swap(x, y);
        }
        res += querySum(rt[c], 1, seg[0], seg[fx], seg[x]);
        x = spr[fx];
        fx = top[x];
    }
    if(dep[x] > dep[y]) std::swap(x, y);
    res += querySum(rt[c], 1, seg[0], seg[x], seg[y]);
    return res;
}
int queryMax(int k, int l, int r, int x, int y)
{
    if(k == 0) return 0;
    if(x <= l && r <= y) return t[k].max;
    int mid = (l + r) >> 1;
    int res = 0;
    if(x <= mid) res = std::max(res, queryMax(t[k].lch, l, mid, x, y));
    if(y > mid) res = std::max(res, queryMax(t[k].rch, mid + 1, r, x, y));
    return res;
}
int askMax(int x, int y, int c)
{
    int fx = top[x];
    int fy = top[y];
    int res = 0;
    while(fx != fy)
    {
        if(dep[fx] < dep[fy])
        {
            std::swap(fx, fy);
            std::swap(x, y);
        }
        res = std::max(res, queryMax(rt[c], 1, seg[0], seg[fx], seg[x]));
        x = spr[fx];
        fx = top[x];
    }
    if(dep[x] > dep[y]) std::swap(x, y);
    res = std::max(res, queryMax(rt[c], 1, seg[0], seg[x], seg[y]));
    return res;
}
int main()
{
    scanf("%d%d", &n, &q);
    for(int i = 1; i <= n; i++) scanf("%d%d", &w[i], &c[i]);
    for(int i = 1; i < n; i++)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        g[u].push_back(v);
        g[v].push_back(u);
    }
    dfs1(1, 0);
    top[1] = seg[1] = rpr[1] = seg[0] = 1;
    dfs2(1);
    for(int i = 1; i <= 1e5; i++) rt[i] = ++pool;
    for(int i = 1; i <= n; i++) update(rt[c[i]], 1, seg[0], seg[i], w[i]);
    for(int i = 1; i <= q; i++)
    {
        char opt[3];
        scanf("%s", opt);
        if(opt[0] == 'C')
        {
            if(opt[1] == 'C')
            {
                int xi, ci;
                scanf("%d%d", &xi, &ci);
                update(rt[c[xi]], 1, seg[0], seg[xi], 0);
                c[xi] = ci;
                update(rt[c[xi]], 1, seg[0], seg[xi], w[xi]);
            }
            else
            {
                int xi, wi;
                scanf("%d%d", &xi, &wi);
                w[xi] = wi;
                update(rt[c[xi]], 1, seg[0], seg[xi], w[xi]);
            }
        }
        else
        {
            if(opt[1] == 'S')
            {
                int x, y;
                scanf("%d%d", &x, &y);
                printf("%d\n", askSum(x, y, c[x]));
            }
            else
            {
                int x, y;
                scanf("%d%d", &x, &y);
                printf("%d\n", askMax(x, y, c[x]));
            }
        }
    }
    return 0;
}
