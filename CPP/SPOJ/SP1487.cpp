#include <cstdio>
#include <algorithm>
#include <vector>
#define N 100007
int n, m, pool, rng;
int l[N];
int _l[N];
std::vector<int> g[N];
struct Node
{
    int lch, rch;
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
int insert(int _k, int l, int r, int x, int v)
{
    int k = ++pool;
    t[k] = t[_k];
    t[k].cnt += v;
    if(l == r) return k;
    int mid = (l + r) >> 1;
    if(x <= mid) t[k].lch = insert(t[_k].lch, l, mid, x, v);
    else t[k].rch = insert(t[_k].rch, mid + 1, r, x, v);
    return k;
}
int seg[N];
int rpr[N];
int rt[N];
int siz[N];
void dfs1(int u, int fa)
{
    seg[u] = ++seg[0];
    rt[seg[u]] = insert(rt[seg[u] - 1], 1, rng, l[u], 1);
    siz[u] = 1;
    int len = g[u].size();
    for(int i = 0; i < len; i++)
    {
        int v = g[u][i];
        if(v == fa) continue;
        dfs1(v, u);
        siz[u] += siz[v];
    }
}
int query(int k1, int k2, int l, int r, int k)
{
    if(l == r) return rpr[l];
    int lsz = t[t[k1].lch].cnt - t[t[k2].lch].cnt;
    int mid = (l + r) >> 1;
    if(k <= lsz) return query(t[k1].lch, t[k2].lch, l, mid, k);
    else return query(t[k1].rch, t[k2].rch, mid + 1, r, k - lsz);   
}
int main()
{
    scanf("%d", &n);
    for(int i = 1; i <= n; i++)
    {
        scanf("%d", &l[i]);
        _l[i] = l[i];
    }
    std::sort(_l + 1, _l + 1 + n);
    rng = std::unique(_l + 1, _l + 1 + n) - (_l + 1);
    for(int i = 1; i <= n; i++)
    {
        l[i] = std::lower_bound(_l + 1, _l + 1 + rng, l[i]) - _l;
        rpr[l[i]] = i;
    }
    for(int i = 1; i < n; i++)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        g[u].push_back(v);
        g[v].push_back(u);
    }
    rt[0] = build(1, rng);
    dfs1(1, 0);
    scanf("%d", &m);
    for(int i = 1; i <= m; i++)
    {
        int x, k;
        scanf("%d%d", &x, &k);
        printf("%d\n", query(rt[seg[x] + siz[x] - 1], rt[seg[x] - 1], 1, rng, k));
    }
    return 0;
}
