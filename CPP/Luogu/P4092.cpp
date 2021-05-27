#include <stdio.h>
#include <algorithm>
#include <vector>
#define N 100007
using namespace std;
int n, q;
vector<int> vec[N];
int dep[N];
int son[N];
int siz[N];
int spr[N];
void dfs1(int s, int u)
{
    dep[u] = dep[s] + 1;
    siz[u] = 1;
    spr[u] = s;
    int len = vec[u].size();
    for(int i = 0; i < len; i++)
    {
        int v = vec[u][i];
        if(v == s)
        {
            continue;
        }
        dfs1(u, v);
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
int tree[4 * N];
void push_up(int k)
{
    tree[k] = max(tree[k << 1], tree[k << 1 | 1]);
}
void build(int k, int l, int r)
{
    if(l == r)
    {
        if(rpr[l] == 1)
        {
            tree[k] = l;
        }
        else
        {
            tree[k] = 0;
        }
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
        tree[k] = l;
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
int ask(int x)
{
    int fx = top[x];
    int ans = 0;
    while(ans == 0)
    {
        ans = query(1, 1, seg[0], seg[fx], seg[x]);
        x = spr[fx];
        fx = top[x];
    }
    return rpr[ans];
}
int main()
{
    scanf("%d%d", &n, &q);
    for(int i = 1; i < n; i++)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        vec[u].push_back(v);
    }
    dfs1(0, 1);
    seg[1] = ++seg[0];
    rpr[seg[1]] = 1;
    top[1] = 1;
    dfs2(1);
    build(1, 1, seg[0]);
    for(int i = 1; i <= q; i++)
    {
        char oper[2];
        int num;
        scanf("%s%d", oper, &num);
        if(oper[0] == 'C')
        {
            change(1, 1, seg[0], seg[num]);
        }
        else
        {
            printf("%d\n", ask(num));
        }
    }
    return 0;
}
