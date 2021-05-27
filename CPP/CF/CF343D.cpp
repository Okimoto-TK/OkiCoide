#include <stdio.h>
#include <algorithm>
#include <vector>
#define N 500007
using namespace std;
int n, q;
vector<int> g[N];
int spr[N];
int son[N];
int dep[N];
int siz[N];
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
int tree[4 * N];
int lazy[4 * N];
void water(int k, int v)
{
    tree[k] = v;
}
void push_up(int k)
{
    tree[k] = ((tree[k << 1] == tree[k << 1 | 1]) && tree[k << 1] != -1 && tree[k << 1 | 1] != -1) ? tree[k << 1] : -1;
}
void push_down(int k)
{
    if(tree[k] == -1)
    {
        return;
    }
    water(k << 1, tree[k]);
    water(k << 1 | 1, tree[k]);
}
void change(int k, int l, int r, int x, int y, int v)
{
    if(x <= l && r <= y)
    {
        water(k, v);
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
        change(1, 1, seg[0], seg[fx], seg[x], 0);
        x = spr[fx];
        fx = top[x];
    }
    if(dep[x] > dep[y])
    {
        swap(x, y);
    }
    change(1, 1, seg[0], seg[x], seg[y], 0);
}
int query(int k, int l, int r, int x)
{
    if(tree[k] != -1)
    {
        return tree[k];
    }
    push_down(k);
    int mid = (l + r) >> 1;
    if(x <= mid)
    {
        return query(k << 1, l, mid, x);
    }
    else
    {
        return query(k << 1 | 1, mid + 1, r, x);
    }
}
int main()
{
    scanf("%d", &n);
    for(int i = 1; i < n; i++)
    {
        int a, b;
        scanf("%d%d", &a, &b);
        g[a].push_back(b);
        g[b].push_back(a);
    }
    dfs1(0, 1);
    seg[1] = ++seg[0];
    rpr[seg[1]] = 1;
    top[1] = 1;
    dfs2(1);
    scanf("%d", &q);
    while(q--)
    {
        int c, u;
        //printf("--%d\n", tree[1]);
        scanf("%d%d", &c, &u);
        if(c == 1)
        {
            change(1, 1, seg[0], seg[u], seg[u] + siz[u] - 1, 1);
        }
        else if(c == 2)
        {
            modify(1, u);
        }
        else
        {
            printf("%d\n", query(1, 1, seg[0], seg[u]));
        }
    }
    return 0;
}
