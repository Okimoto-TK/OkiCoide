#include <stdio.h>
#include <vector>
using namespace std;

int g_n, g_m;
int g_sup[100007];
int g_son[100007];
int g_seg[100007];
int g_siz[100007];
int g_dep[100007];
int g_top[100007];
int g_num[100007];
int g_ref[100007];
long long g_t[400007];
long long g_lzy[400007];
vector <int> g_vec[100007];

// PreProc
void dfsOne(int u, int sup)
{
    g_sup[u] = sup;
    g_siz[u] = 1;
    g_dep[u] = g_dep[sup] + 1;
    for(int i = 0; i < g_vec[u].size(); ++i)
    {
        int v = g_vec[u][i];
        if(v == sup){ continue; }
        dfsOne(v, u);
        g_siz[u] += g_siz[v];
        if(g_siz[v] > g_siz[g_son[u]]){ g_son[u] = v; }
    }
}
void dfsTwo(int u, int sup)
{
    if(g_son[u])
    {
        int v = g_son[u];
        g_seg[v] = ++g_seg[0];
        g_ref[g_seg[0]] = v;
        g_top[v] = g_top[u];
        dfsTwo(v, u);
    }
    for(int i = 0; i < g_vec[u].size(); ++i)
    {
        int v = g_vec[u][i];
        if(v == sup || v == g_son[u]){ continue; }
        g_seg[v] = ++g_seg[0];
        g_ref[g_seg[0]] = v;
        g_top[v] = v;
        dfsTwo(v, u);
    }
}

// SegTree
void con(int k, int l, int r)
{
    if(l == r)
    {
        g_t[k] = g_num[g_ref[l]];
        return;
    }
    int mid = (l + r) >> 1;
    con(k << 1, l, mid);
    con((k << 1) | 1, mid + 1, r);
    g_t[k] = g_t[k << 1] + g_t[(k << 1) | 1];
}
void inc(int k, int l, int r, int v)
{
    g_t[k] += (r - l + 1) * v;
    g_lzy[k] += v;
}
void psh(int k, int l, int r)
{
    if(g_lzy[k] == 0){ return; }
    int mid = (l + r) >> 1;
    inc(k << 1, l, mid, g_lzy[k]);
    inc((k << 1) | 1, mid + 1, r, g_lzy[k]);
    g_lzy[k] = 0;
}
void mod(int k, int l, int r, int x, int y)
{
    if(x <= l && r <= y){ return inc(k, l, r, 1); }
    psh(k, l, r);
    int mid = (l + r) >> 1;
    if(x <= mid){ mod(k << 1, l, mid, x, y); }
    if(y > mid){ mod((k << 1) | 1, mid + 1, r, x, y); }
    g_t[k] = g_t[k << 1] + g_t[(k << 1) | 1];
}
void _mod(int k, int l, int r, int x, int y)
{
    if(x <= l && r <= y){ return inc(k, l, r, -1); }
    psh(k, l, r);
    int mid = (l + r) >> 1;
    if(x <= mid){ _mod(k << 1, l, mid, x, y); }
    if(y > mid){ _mod((k << 1) | 1, mid + 1, r, x, y); }
    g_t[k] = g_t[k << 1] + g_t[(k << 1) | 1];
}
long long req(int k, int l, int r, int x, int y)
{
    if(x <= l && r <= y){ return g_t[k]; }
    psh(k, l, r);
    int mid = (l + r) >> 1;
    long long res = 0;
    if(x <= mid){ res += req(k << 1, l, mid, x, y); }
    if(y > mid){ res += req((k << 1) | 1, mid + 1, r, x, y); }
    return res;
}

// HLD
inline void swp(int &x, int &y){ int t = x; x = y; y = t; }
void set(int x, int y)
{
    int fx = g_top[x];
    int fy = g_top[y];
    while(fx != fy)
    {
        if(g_dep[fx] < g_dep[fy])
        {
            swp(x, y);
            swp(fx, fy);
        }
        mod(1, 1, g_seg[0], g_seg[fx], g_seg[x]);
        x = g_sup[fx];
        fx = g_top[x];
    }
    if(g_dep[x] > g_dep[y]){ swp(x, y); }
    mod(1, 1, g_seg[0], g_seg[x], g_seg[y]);
    _mod(1, 1, g_seg[0], g_seg[x], g_seg[x]);
}
long long get(int x, int y)
{
    long long res = 0;
    int fx = g_top[x];
    int fy = g_top[y];
    while(fx != fy)
    {
        if(g_dep[fx] < g_dep[fy])
        {
            swp(x, y);
            swp(fx, fy);
        }
        res += req(1, 1, g_seg[0], g_seg[fx], g_seg[x]);
        x = g_sup[fx];
        fx = g_top[x];
    }
    if(g_dep[x] > g_dep[y]){ swp(x, y); }
    res += req(1, 1, g_seg[0], g_seg[x], g_seg[y]);
    res -= req(1, 1, g_seg[0], g_seg[x], g_seg[x]);
    return res;
}

// Main
int main()
{
    scanf("%d%d", &g_n, &g_m);
    for(int i = 1; i < g_n; ++i)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        g_vec[u].push_back(v);
        g_vec[v].push_back(u);
    }
    dfsOne(1, 1);
    g_seg[1] = ++g_seg[0];
    g_ref[g_seg[0]] = 1;
    g_top[1] = 1;
    dfsTwo(1, 1);
    con(1, 1, g_seg[0]);
    for(int i = 0; i < g_m; ++i)
    {
        char opt[3];
        int x, y;
        scanf("%s", opt);
        scanf("%d%d", &x, &y);
        if(opt[0] == 'P'){ set(x, y); }
        else{ printf("%lld\n", get(x, y)); }
    }
    return 0;
}
