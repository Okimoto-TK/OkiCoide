#include <cstdio>
#define N 500007
int n, m, pool;
int a[N];
struct Node
{
    int lch;
    int rch;
    int cnt;
    Node() { lch = rch = cnt = 0; }
} t[20000000];
int rt[N];
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
    if(l == r)
    {
        t[k].cnt = t[_k].cnt + 1;
        return k;
    }
    int mid = (l + r) >> 1;
    t[k].lch = t[_k].lch;
    t[k].rch = t[_k].rch;
    if(x <= mid) t[k].lch = insert(t[k].lch, l, mid, x);
    else t[k].rch = insert(t[k].rch, mid + 1, r, x);
    t[k].cnt = t[t[k].lch].cnt + t[t[k].rch].cnt;
    return k;
}
int query(int lr, int rr, int l, int r, int k)
{
    if(t[rr].cnt - t[lr].cnt <= k) return 0;
    if(l == r) return l;
    int mid = (l + r) >> 1;
    return query(t[lr].lch, t[rr].lch, l, mid, k) + query(t[lr].rch, t[rr].rch, mid + 1, r, k);
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
    for(int i = 1; i <= m; i++)
    {
        int l, r;
        scanf("%d%d", &l, &r);
        printf("%d\n", query(rt[l - 1], rt[r], 1, N, (r - l + 1) / 2));
    }
    return 0;
}
