#include <cstdio>
#include <algorithm>
#define N 100007
int n, m, pool;
int a[N];
int b[N];
int rt[N];
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
int insert(int _k, int l, int r, int x)
{
    int k = ++pool;
    t[k] = t[_k];
    t[k].cnt += 1;
    if(l == r) return k;
    int mid = (l + r) >> 1;
    if(x <= mid) t[k].lch = insert(t[_k].lch, l, mid, x);
    else t[k].rch = insert(t[_k].rch, mid + 1, r, x);
    return k;
}
int query(int k1, int k2, int l, int r, int k)
{
    if(l == r) return b[l];
    int mid = (l + r) >> 1;
    int diff = t[t[k1].lch].cnt - t[t[k2].lch].cnt;
    if(k <= diff) return query(t[k1].lch, t[k2].lch, l, mid, k);
    else return query(t[k1].rch, t[k2].rch, mid + 1, r, k - diff);
}
int main()
{
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= n; i++)
    {
        scanf("%d", &a[i]);
        b[i] = a[i];
    }
    std::sort(b + 1, b + 1 + n);
    int len = std::unique(b + 1, b + 1 + n) - (b + 1);
    rt[0] = build(1, len);
    for(int i = 1; i <= n; i++)
    {
        a[i] = std::lower_bound(b + 1, b + 1 + len, a[i]) - b;
        rt[i] = insert(rt[i - 1], 1, len, a[i]);
    }
    for(int i = 1; i <= m; i++)
    {
        int l, r, k;
        scanf("%d%d%d", &l, &r, &k);
        printf("%d\n", query(rt[r], rt[l - 1], 1, len, k));
    }
    return 0;
}
