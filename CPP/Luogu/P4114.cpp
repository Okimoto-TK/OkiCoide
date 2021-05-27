#include <stdio.h>
#include <vector>
#include <algorithm>
#define N 100007
using namespace std;
int n;
vector<pair<pair<int, int>, int> > g[N];
int son[N];
int siz[N];
int dep[N];
int spr[N];
int wgt[N];
int map[N];
void dfs1(int s, int u)
{
    dep[u] = dep[s] + 1;
    spr[u] = s;
    siz[u] = 1;
    int len = g[u].size();
    for(int i = 0; i < len; i++)
    {
        int v = g[u][i].first.first;
        if(v == s)
        {
            continue;
        }
        dfs1(u, v);
        wgt[v] = g[u][i].first.second;
        map[g[u][i].second] = v;
        siz[u] += siz[v];
        if(siz[son[u]] < siz[v])
        {
            son[u] = v;
        }
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
        rpr[seg[v]] = v;
        top[v] = top[u];
        dfs2(v);
    }
    int len = g[u].size();
    for(int i = 0; i < len; i++)
    {
        int v = g[u][i].first.first;
        if(top[v])
        {
            continue;
        }
        seg[v] = ++seg[0];
        rpr[seg[v]] = v;
        top[v] = v;
        dfs2(v);
    }
}
int tree[4 * N];
void push_up(int k)
{
    tree[k] = max(tree[k << 1], tree[k << 1 | 1]);
}
void build(int k, int l, int r)
{
    if(l == r)
    {
        tree[k] = wgt[rpr[l]];
        return;
    }
    int mid = (l + r) >> 1;
    build(k << 1, l, mid);
    build(k << 1 | 1, mid + 1, r);
    push_up(k);
}
void change(int k, int l, int r, int x, int v)
{
    if(l == r)
    {
        tree[k] = v;
        return;
    }
    int mid = (l + r) >> 1;
    if(x <= mid)
    {
        change(k << 1, l, mid, x, v);
    }
    else
    {
        change(k << 1 | 1, mid + 1, r, x, v);
    }
    push_up(k);
}
int query(int k, int l, int r, int x, int y)
{
    if(x <= l && r <= y)
    {
        return tree[k];
    }
    int mid = (l + r) >> 1;
    int res = 0;
    if(x <= mid)
    {
        res = max(query(k << 1, l, mid, x, y), res);
    }
    if(y > mid)
    {
        res = max(query(k << 1 | 1, mid + 1, r, x, y), res);
    }
    return res;
}
int ask(int x, int y)
{
    int fx = top[x];
    int fy = top[y];
    int res = 0;
    while(fx != fy)
    {
        if(dep[fx] < dep[fy])
        {
            swap(fx, fy);
            swap(x, y);
        }
        res = max(res, query(1, 1, seg[0], seg[fx], seg[x]));
        x = spr[fx];
        fx = top[x];
    }
    if(x == y)
    {
        return res;
    }
    if(dep[x] > dep[y])
    {
        swap(x, y);
    }
    res = max(res, query(1, 1, seg[0], seg[son[x]], seg[y]));
    return res;
}
int main()
{
    scanf("%d", &n);
    for(int i = 1; i < n; i++)
    {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        g[u].push_back(pair<pair<int, int>, int>(pair<int, int>(v, w), i));
        g[v].push_back(pair<pair<int, int>, int>(pair<int, int>(u, w), i));
    }
    dfs1(0, 1);
    seg[1] = ++seg[0];
    rpr[seg[1]] = 1;
    top[1] = 1;
    dfs2(1);
    build(1, 1, seg[0]);
    while(true)
    {
        char opt[7];
        scanf("%s", opt);
        if(opt[0] == 'Q')
        {
            int a, b;
            scanf("%d%d", &a, &b);
            printf("%d\n", ask(a, b));
        }
        else if(opt[0] == 'C')
        {
            int x, t;
            scanf("%d%d", &x, &t);
            change(1, 1, seg[0], seg[map[x]], t);
        }
        else
        {
            return 0;
        }
    }
}
