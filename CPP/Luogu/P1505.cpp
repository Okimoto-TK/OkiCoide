#include <stdio.h>
#include <vector>
#include <algorithm>
using namespace std;
int n, m;
int son[200007];
int spr[200007];
int top[200007];
int dep[200007];
int seg[200007];
int rpr[200007];
int wgt[200007];
int map[200007];
int size[200007];
int trum[900007];
int trax[900007];
int trin[900007];
int lazy[900007];
vector<pair<pair<int, int>, int> > g[200007];
void dfs1(int s, int u)
{
    dep[u] = dep[s] + 1;
    size[u] = 1;
    spr[u] = s;
    int len = g[u].size();
    for(int i = 0; i < len; i++)
    {
        int v = g[u][i].first.first;
        int w = g[u][i].first.second;
        int t = g[u][i].second;
        if(v == s)
        {
            continue;
        }
        wgt[v] = w;
        map[t] = v;
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
        rpr[seg[0]] = v;
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
        rpr[seg[0]] = v;
        top[v] = v;
        dfs2(v);
    }
}
void push_up(int k)
{
    trax[k] = max(trax[k << 1], trax[k << 1 | 1]);
    trin[k] = min(trin[k << 1], trin[k << 1 | 1]);
    trum[k] = trum[k << 1] + trum[k << 1 | 1];
}
void build(int k, int l, int r)
{
    lazy[k] = 1;
    if(l == r)
    {
        trax[k] = wgt[rpr[l]];
        trin[k] = wgt[rpr[l]];
        trum[k] = wgt[rpr[l]];
        return;
    }
    int mid = (l + r) >> 1;
    build(k << 1, l, mid);
    build(k << 1 | 1, mid + 1, r);
    push_up(k);
}
void times(int k)
{
    trum[k] *= -1;
    int _max = trax[k];
    trax[k] = -1 * trin[k];
    trin[k] = -1 * _max;
    lazy[k] *= -1;
}
void push_down(int k)
{
    if(lazy[k] == 1)
    {
        return;
    }
    times(k << 1);
    times(k << 1 | 1);
    lazy[k] = 1;
}
void multi(int k, int l, int r, int x, int y)
{
    if(x <= l && r <= y)
    {
        times(k);
        return;
    }
    push_down(k);
    int mid = (l + r) >> 1;
    if(x <= mid)
    {
        multi(k << 1, l, mid, x, y);
    }
    if(y > mid)
    {
        multi(k << 1 | 1, mid + 1, r, x, y);
    }
    push_up(k);
}
void change(int k, int l, int r, int x, int v)
{
    if(l == r)
    {
        trax[k] = v;
        trin[k] = v;
        trum[k] = v;
        return;
    }
    push_down(k);
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
int query_sum(int k, int l, int r, int x, int y)
{
    if(x <= l && r <= y)
    {
        return trum[k];
    }
    push_down(k);
    int mid = (l + r) >> 1;
    int res = 0;
    if(x <= mid)
    {
        res += query_sum(k << 1, l, mid, x, y);
    }
    if(y > mid)
    {
        res += query_sum(k << 1 | 1, mid + 1, r, x, y);
    }
    return res;
}
int query_max(int k, int l, int r, int x, int y)
{
    if(x <= l && r <= y)
    {
        return trax[k];
    }
    push_down(k);
    int mid = (l + r) >> 1;
    int res = 0x3f3f3f3f;
    res *= -1;
    if(x <= mid)
    {
        res = max(query_max(k << 1, l, mid, x, y), res);
    }
    if(y > mid)
    {
        res = max(query_max(k << 1 | 1, mid + 1, r, x, y), res);
    }
    return res;
}
int query_min(int k, int l, int r, int x, int y)
{
    if(x <= l && r <= y)
    {
        return trin[k];
    }
    push_down(k);
    int mid = (l + r) >> 1;
    int res = 0x3f3f3f3f;
    if(x <= mid)
    {
        res = min(query_min(k << 1, l, mid, x, y), res);
    }
    if(y > mid)
    {
        res = min(query_min(k << 1 | 1, mid + 1, r, x, y), res);
    }
    return res;
}
void modify(int x, int y)
{
    int fx = top[x];
    int fy = top[y];
    while(fx != fy)
    {
        if(dep[fx] < dep[fy])
        {
            swap(fx, fy);
            swap(x, y);
        }
        multi(1, 1, seg[0], seg[fx], seg[x]);
        x = spr[fx];
        fx = top[x];
    }
    if(x == y)
    {
        return;
    }
    if(dep[x] > dep[y])
    {
        swap(x, y);
    }
    multi(1, 1, seg[0], seg[son[x]], seg[y]);
}
int ask_sum(int x, int y)
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
        res += query_sum(1, 1, seg[0], seg[fx], seg[x]);
        x = spr[fx];
        fx = top[x];
    }
    if(dep[x] > dep[y])
    {
        swap(x, y);
    }
    if(x == y)
    {
        return res;
    }
    res += query_sum(1, 1, seg[0], seg[son[x]], seg[y]);
    return res;
}
int ask_max(int x, int y)
{
    int fx = top[x];
    int fy = top[y];
    int res = 0x3f3f3f3f;
    res *= -1;
    while(fx != fy)
    {
        if(dep[fx] < dep[fy])
        {
            swap(fx, fy);
            swap(x, y);
        }
        res = max(res, query_max(1, 1, seg[0], seg[fx], seg[x]));
        x = spr[fx];
        fx = top[x];
    }
    if(dep[x] > dep[y])
    {
        swap(x, y);
    }
    if(x == y)
    {
        return res;
    }
    res = max(res, query_max(1, 1, seg[0], seg[son[x]], seg[y]));
    return res;
}
int ask_min(int x, int y)
{
    int fx = top[x];
    int fy = top[y];
    int res = 0x3f3f3f3f;
    while(fx != fy)
    {
        if(dep[fx] < dep[fy])
        {
            swap(fx, fy);
            swap(x, y);
        }
        res = min(res, query_min(1, 1, seg[0], seg[fx], seg[x]));
        x = spr[fx];
        fx = top[x];
    }
    if(dep[x] > dep[y])
    {
        swap(x, y);
    }
    if(x == y)
    {
        return res;
    }
    res = min(res, query_min(1, 1, seg[0], seg[son[x]], seg[y]));
    return res;
}
int main()
{
    scanf("%d", &n);
    for(int i = 1; i < n; i++)
    {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        u++;
        v++;
        g[u].push_back(pair<pair<int, int>, int>(pair<int, int>(v, w), i));
        g[v].push_back(pair<pair<int, int>, int>(pair<int, int>(u, w), i));
    }
    dfs1(0, 1);
    top[1] = 1;
    seg[1] = 1;
    seg[0] = 1;
    rpr[1] = 1;
    dfs2(1);
    build(1, 1, seg[0]);
    scanf("%d", &m);
    while(m--)
    {
        char opt[4];
        scanf("%s", opt);
        if(opt[0] == 'C')
        {
            int i, w;
            scanf("%d%d", &i, &w);
            change(1, 1, seg[0], seg[map[i]], w);
        }
        else if(opt[0] == 'N')
        {
            int u, v;
            scanf("%d%d", &u, &v);
            u++;
            v++;
            modify(u, v);
        }
        else if(opt[0] == 'S')
        {
            int u, v;
            scanf("%d%d", &u, &v);
            u++;
            v++;
            printf("%d\n", ask_sum(u, v));
        }
        else if(opt[1] == 'A')
        {
            int u, v;
            scanf("%d%d", &u, &v);
            u++;
            v++;
            printf("%d\n", ask_max(u, v));
        }
        else
        {
            int u, v;
            scanf("%d%d", &u, &v);
            u++;
            v++;
            printf("%d\n", ask_min(u, v));
        }
    }
    return 0;
}
