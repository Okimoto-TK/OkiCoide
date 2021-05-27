#include <stdio.h>
#include <vector>
#include <algorithm>
using namespace std;
int n, q;
int son[100007];
int spr[100007];
int seg[100007];
int rpr[100007];
int top[100007];
int dep[100007];
int size[100007];
long long tree[400007];
long long lazy[400007];
vector <int> vec[100007];
void dfs1(int s, int u)
{
    size[u] = 1;
    spr[u] = s;
    dep[u] = dep[s] + 1;
    int len = vec[u].size();
    for(int i = 0; i < len; i++)
    {
        int v = vec[u][i];
        if(v == s)
        {
            continue;
        }
        dfs1(u, v);
        size[u] += size[v];
        if(size[v] > size[son[u]])
        {
            son[u] = v;
        }
    }
}
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
    int len = vec[u].size();
    for(int i = 0; i < len; i++)
    {
        int v = vec[u][i];
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
void add(int k, int l, int r, long long v)
{
    tree[k] += (r - l + 1) * v;
    lazy[k] += v;
}
void push_down(int k, int l, int r)
{
    if(lazy[k] == 0)
    {
        return;
    }
    int mid = (l + r) >> 1;
    add(k << 1, l, mid, lazy[k]);
    add(k << 1 | 1, mid + 1, r, lazy[k]);
    lazy[k] = 0;
}
void change(int k, int l, int r, int x, int y, long long v)
{
    if(x <= l && r <= y)
    {
        add(k, l, r, v);
        return;
    }
    push_down(k, l, r);
    int mid = (l + r) >> 1;
    if(x <= mid)
    {
        change(k << 1, l, mid, x, y, v);
    }
    if(y > mid)
    {
        change(k << 1 | 1, mid + 1, r, x, y, v);
    }
    tree[k] = tree[k << 1] + tree[k << 1 | 1];
}
long long query(int k, int l, int r, int x, int y)
{
    if(x <= l && r <= y)
    {
        return tree[k];
    }
    push_down(k, l, r);
    int mid = (l + r) >> 1;
    long long res = 0;
    if(x <= mid)
    {
        res += query(k << 1, l, mid, x, y);
    }
    if(y > mid)
    {
        res += query(k << 1 | 1, mid + 1, r, x, y);
    }
    return res;
}
void modify(int x, int y, long long v)
{
    int fx = top[x];
    int fy = top[y];
    while(fx != fy)
    {
        if(dep[fx] < dep[fy])
        {
            swap(x, y);
            swap(fx, fy);
        }
        change(1, 1, seg[0], seg[fx], seg[x], v);
        x = spr[fx];
        fx = top[x];
    }
    if(dep[x] > dep[y])
    {
        swap(x, y);
    }
    change(1, 1, seg[0], seg[x], seg[y], v);
}
long long ask(int x)
{
    return query(1, 1, seg[0], seg[x], seg[x] + size[x] - 1);
}
int main()
{
    scanf("%d", &n);
    for(int i = 1; i < n; i++)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        vec[u + 1].push_back(v + 1);
    }
    dfs1(0, 1);
    seg[1] = ++seg[0];
    rpr[seg[0]] = 1;
    top[1] = 1;
    dfs2(1);
    scanf("%d", &q);
    for(int i = 1; i <= q; i++)
    {
        char opt[2];
        scanf("%s", opt);
        if(opt[0] == 'A')
        {
            int u, v;
            long long d;
            scanf("%d%d%lld", &u, &v, &d);
            modify(u + 1, v + 1, d);
        }
        else
        {
            int u;
            scanf("%d", &u);
            printf("%lld\n", ask(u + 1));
        }
    }
    return 0;
}
