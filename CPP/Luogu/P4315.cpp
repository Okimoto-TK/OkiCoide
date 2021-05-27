#include <stdio.h>
#include <algorithm>
#include <vector>
#define N 100007
using namespace std;
int n;
vector<pair<pair<int, int>, int> > vec[N];
int son[N];
int spr[N];
int dep[N];
int siz[N];
int wgt[N];
int map[N];
void dfs1(int s, int u)
{
    dep[u] = dep[s] + 1;
    siz[u] = 1;
    spr[u] = s;
    int len = vec[u].size();
    for(int i = 0; i < len; i++)
    {
        int v = vec[u][i].first.first;
        if(v == s)
        {
            continue;
        }
        dfs1(u, v);
        wgt[v] = vec[u][i].first.second;
        map[vec[u][i].second] = v;
        siz[u] += siz[v];
        if(siz[v] > siz[son[u]])
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
    int len = vec[u].size();
    for(int i = 0; i < len; i++)
    {
        int v = vec[u][i].first.first;
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
int lazy[4 * N];
int buff[4 * N];
void push_up(int k)
{
    tree[k] = max(tree[k << 1], tree[k << 1 | 1]);
}
void build(int k, int l, int r)
{
    buff[k] = -1;
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
void add(int k, int v)
{
    tree[k] += v;
    lazy[k] += v;
}
void cover(int k, int v)
{
    tree[k] = v;
    lazy[k] = 0;
    buff[k] = v;
}
void push_down(int k)
{
    if(buff[k] != -1)
    {
        cover(k << 1, buff[k]);
        cover(k << 1 | 1, buff[k]);
        buff[k] = -1;
    }
    if(lazy[k] == 0)
    {
        return;
    }
    add(k << 1, lazy[k]);
    add(k << 1 | 1, lazy[k]);
    lazy[k] = 0;
}
void change(int k, int l, int r, int x, int y, int v)
{
    if(x <= l && r <= y)
    {
        cover(k, v);
        return;
    }
    push_down(k);
    int mid = (l + r) >> 1;
    if(x <= mid)
    {
        change(k << 1, l, mid, x, y, v);
    }
    if(y > mid)
    {
        change(k << 1 | 1, mid + 1, r, x, y, v);
    }
    push_up(k);
}
void plus(int k, int l, int r, int x, int y, int v)
{
    if(x <= l && r <= y)
    {
        add(k, v);
        return;
    }
    push_down(k);
    int mid = (l + r) >> 1;
    if(x <= mid)
    {
        plus(k << 1, l, mid, x, y, v);
    }
    if(y > mid)
    {
        plus(k << 1 | 1, mid + 1, r, x, y, v);
    }
    push_up(k);
}
int query(int k, int l, int r, int x, int y)
{
    if(x <= l && r <= y)
    {
        return tree[k];
    }
    push_down(k);
    int mid = (l + r) >> 1;
    int res = 0;
    if(x <= mid)
    {
        res = max(res, query(k << 1, l, mid, x, y));
    }
    if(y > mid)
    {
        res = max(res, query(k << 1 | 1, mid + 1, r, x, y));
    }
    return res;
}
void modify(int x, int y, int v)
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
        change(1, 1, seg[0], seg[fx], seg[x], v);
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
    change(1, 1, seg[0], seg[son[x]], seg[y], v);
}
void inc(int x, int y, int v)
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
        plus(1, 1, seg[0], seg[fx], seg[x], v);
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
    plus(1, 1, seg[0], seg[son[x]], seg[y], v);
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
        vec[u].push_back(pair<pair<int, int>, int>(pair<int, int>(v, w), i));
        vec[v].push_back(pair<pair<int, int>, int>(pair<int, int>(u, w), i));
    }
    dfs1(0, 1);
    seg[1] = ++seg[0];
    rpr[seg[1]] = 1;
    top[1] = 1;
    dfs2(1);
    build(1, 1, seg[0]);
    char op[10];
    scanf("%s", op);
    while(op[0] != 'S')
    {
        if(op[0] == 'C')
        {
            if(op[1] == 'h')
            {
                int k, w;
                scanf("%d%d", &k, &w);
                change(1, 1, seg[0], seg[map[k]], seg[map[k]], w);
            }
            else
            {
                int u, v, w;
                scanf("%d%d%d", &u, &v, &w);
                modify(u, v, w);
            }
        }
        else if(op[0] == 'A')
        {
            int u, v, w;
            scanf("%d%d%d", &u, &v, &w);
            inc(u, v, w);
        }
        else
        {
            int u, v;
            scanf("%d%d", &u, &v);
            printf("%d\n", ask(u, v));
        }
        scanf("%s", op);
    }
    return 0;
}
