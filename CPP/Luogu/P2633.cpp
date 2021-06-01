#include <cstdio>
#include <vector>
#include <algorithm>
#define N 100007
int n, m, pool;
long long a[N];
long long b[N];
std::vector<int> g[N];
int siz[N];
int son[N];
int spr[N];
int dep[N];
void dfs1(int u, int fa)
{
    dep[u] = dep[fa] + 1;
    siz[u] = 1;
    spr[u] = fa;
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
int rt[N];
struct Node
{
    int lch;
    int rch;
    int cnt;
    Node() { lch = rch = cnt = 0; }
} t[8000000];
int build(int l, int r)
{
    int k = ++pool;
    if(l == r) return k;
    int mid = (l + r) >> 1;
    t[k].lch = build(l, mid);
    t[k].rch = build(mid + 1, r);
    return k;
}
int insert(int _k, int l, int r, int x)
{
    int k = ++pool;
    if(l == r)
    {
        t[k].cnt = t[_k].cnt + 1;
        return k;
    }
    int mid = (l + r) >> 1;
    t[k].lch = t[_k].lch;
    t[k].rch = t[_k].rch;
    if(x <= mid) t[k].lch = insert(t[k].lch, l, mid, x);
    else t[k].rch = insert(t[k].rch, mid + 1, r, x);
    t[k].cnt = t[t[k].lch].cnt + t[t[k].rch].cnt;
    return k;
}
int top[N];
void dfs2(int u)
{
    rt[u] = insert(rt[spr[u]], 1, N, a[u]);
    if(son[u])
    {
        int v = son[u];
        top[v] = top[u];
        dfs2(v);
    }
    int len = g[u].size();
    for(int i = 0; i < len; i++)
    {
        int v = g[u][i];
        if(top[v] != 0) continue;
        top[v] = v;
        dfs2(v);
    }
}
int getLCA(int x, int y)
{
    int fx = top[x];
    int fy = top[y];
    while(fx != fy)
    {
        if(dep[fx] < dep[fy])
        {
            std::swap(fx, fy);
            std::swap(x, y);
        }
        x = spr[fx];
        fx = top[x];
    }
    return dep[x] > dep[y] ? y : x;
}
long long query(int ur, int vr, int lr, int fr, int l, int r, int k)
{
    if(l == r) return b[l];
    int lval = t[t[ur].lch].cnt + t[t[vr].lch].cnt - t[t[lr].lch].cnt - t[t[fr].lch].cnt;
    int mid = (l + r) >> 1;
    if(k <= lval) return query(t[ur].lch, t[vr].lch, t[lr].lch, t[fr].lch, l, mid, k);
    else return query(t[ur].rch, t[vr].rch, t[lr].rch, t[fr].rch, mid + 1, r, k - lval);
}
int main()
{
    //freopen("in.in", "r", stdin);
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= n; i++)
    {
        scanf("%lld", &a[i]);
        b[i] = a[i];
    }
    std::sort(b + 1, b + 1 + n);
    int len = std::unique(b + 1, b + 1 + n) - (b + 1);
    for(int i = 1; i <= n; i++) a[i] = std::lower_bound(b + 1, b + 1 + len, a[i]) - b;
    for(int i = 1; i < n; i++)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        g[u].push_back(v);
        g[v].push_back(u);
    }
    dfs1(1, 0);
    rt[0] = build(1, N);
    top[1] = 1;
    dfs2(1);
    long long last = 0;
    for(int i = 1; i <= m; i++)
    {
        long long u;
        int v, k;
        scanf("%lld%d%d", &u, &v, &k);
        u ^= last;
        //printf("%d\n", u);
        int lca = getLCA(u, v);
        last = query(rt[u], rt[v], rt[lca], rt[spr[lca]], 1, N, k);
        printf("%lld\n", last);
    }
    return 0;
}
