#include <cstdio>
#include <algorithm>
#define N 300007
int n, m, pool;
int a[N];
int rt[N];
struct node
{
    int lc;
    int rc;
    int vl;
    node() { lc = rc = vl = 0; };
} t[N << 4];
void push_up(int k) { t[k].vl = t[t[k].lc].vl + t[t[k].rc].vl; }
int build(int l, int r)
{
    int k = ++pool;
    if(l == r)  return k;
    int mid = (l + r) >> 1;
    t[k].lc = build(l, mid);
    t[k].rc = build(mid + 1, r);
    push_up(k);
    return k;
}
int insert(int _k, int l, int r, int x)
{
    int k = ++pool;
    if(l == r)
    {
        t[k].vl = t[_k].vl + 1;
        return k;
    }
    t[k].lc = t[_k].lc;
    t[k].rc = t[_k].rc;
    int mid = (l + r) >> 1;
    if(x <= mid) t[k].lc = insert(t[k].lc, l, mid, x);
    else t[k].rc = insert(t[k].rc, mid + 1, r, x);
    push_up(k);
    return k;
}
int query(int k, int l, int r, int x)
{
    if(l == r) return t[k].vl;
    int mid = (l + r) >> 1;
    int res = 0;
    if(x <= mid) res += query(t[k].lc, l, mid, x);
    else res += query(t[k].rc, mid + 1, r, x);
    return res;
}
int get()
{
    int l, r, c;
    scanf("%d%d%d", &l, &r, &c);
    return query(rt[r], 1, N, c) - query(rt[l - 1], 1, N, c);
}
void change(int k, int l, int r, int x, int v)
{
    if(l == r)
    {
        t[k].vl += v;
        return;
    }
    int mid = (l + r) >> 1;
    if(x <= mid) change(t[k].lc, l, mid, x, v);
    else change(t[k].rc, mid + 1, r, x, v);
    push_up(k);
}
void set()
{
    int x;
    scanf("%d", &x);
    change(rt[x], 1, N, a[x], -1);
    std::swap(a[x], a[x + 1]);
    change(rt[x], 1, N, a[x], 1);
}
int main()
{
    scanf("%d%d", &n, &m);
    rt[0] = build(1, N);
    for(int i = 1; i <= n; i++)
    {
        scanf("%d", &a[i]);
        rt[i] = insert(rt[i - 1], 1, N, a[i]);
    }
    for(; m != 0; m--)
    {
        int opt;
        scanf("%d", &opt);
        if(opt == 1) printf("%d\n", get());
        if(opt == 2) set();
    }
    return 0;
}

