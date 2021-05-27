#include <stdio.h>
#include <vector>
#include <algorithm>
#define N 100007
using namespace std;
int n, q;
vector<int> g[N];
int son[N];
int spr[N];
int siz[N];
int dep[N];
void dfs1(int s, int u)
{
    dep[u] = dep[s] + 1;
    siz[u] = 1;
    spr[u] = s;
    int len = g[u].size();
    for(int i = 0; i < len; i++)
    {
        int v = g[u][i];
        if(v == s)
        {
            continue;
        }
        dfs1(u, v);
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
        int v = g[u][i];
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
int tree[N << 2];
void push_up(int k)
{
    tree[k] = min(tree[k << 1], tree[k << 1 | 1]);
}
void build(int k, int l, int r)
{
    if(l == r)
    {
        tree[k] = N - 6;
        return;
    }
    int mid = (l + r) >> 1;
    build(k << 1, l, mid);
    build(k << 1 | 1, mid + 1, r);
    push_up(k);
}
void change(int k, int l, int r, int x)
{
    if(l == r)
    {
        if(tree[k] == N - 6)
        {
            tree[k] = l;
        }
        else
        {
            tree[k] = N - 6;
        }
        return;
    }
    int mid = (l + r) >> 1;
    if(x <= mid)
    {
        change(k << 1, l, mid, x);
    }
    else
    {
        change(k << 1 | 1, mid + 1, r, x);
    }
    push_up(k);
}
int query(int k, int l, int r, int x, int y)
{
    if(x <= l && r <= y)
    {
        return tree[k];
    }
    int res = N - 6;
    int mid = (l + r) >> 1;
    if(x <= mid)
    {
        res = min(res, query(k << 1, l, mid, x, y));
    }
    if(y > mid)
    {
        res = min(res, query(k << 1 | 1, mid + 1, r, x, y));
    }
    return res;
}
int ask(int x)
{
    int fx = top[x];
    int res = N - 6;
    while(fx != 1)
    {
        res = min(res, query(1, 1, seg[0], seg[fx], seg[x]));
        x = spr[fx];
        fx = top[x];
    }
    res = min(res, query(1, 1, seg[0], seg[1], seg[x]));
    return rpr[res];
}
int main()
{
    rpr[N - 6] = -1;
    scanf("%d%d", &n, &q);
    for(int i = 1; i < n; i++)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        g[u].push_back(v);
        g[v].push_back(u);
    }
    dfs1(0, 1);
    seg[1] = ++seg[0];
    rpr[seg[1]] = 1;
    top[1] = 1;
    dfs2(1);
    build(1, 1, seg[0]);
    for(int i = 1; i <= q; i++)
    {
        int op, v;
        scanf("%d%d", &op, &v);
        if(op == 0)
        {
            change(1, 1, seg[0], seg[v]);
        }
        else
        {
            printf("%d\n", ask(v));
        }
    }
    return 0;
}
