#include <cstdio>
#include <algorithm>
#define N 200007
#define T 200007
int m, n, pool;
int rt[N];
int b[N];
struct Node
{
    int lch, rch;
    long long cnt, val;
} t[10000000];
struct Buff
{
    int x;
    int v;
} q[N * 2];
bool cmp(Buff a, Buff b)
{
    return a.x < b.x;
}
int build(int l, int r)
{
    int k = ++pool;
    if(l == r) return k;
    int mid = (l + r) >> 1;
    t[k].lch = build(l, mid);
    t[k].rch = build(mid + 1, r);
    return k;
}
int insert(int _k, int l, int r, int x, int v)
{
    int k = ++pool;
    t[k] = t[_k];
    if(l == r)
    {
        t[k].cnt += v;
        t[k].val += v * b[x];
        return k;
    }
    int mid = (l + r) >> 1;
    if(x <= mid) t[k].lch = insert(t[k].lch, l, mid, x, v);
    else t[k].rch = insert(t[k].rch, mid + 1, r, x, v);
    t[k].cnt = t[t[k].lch].cnt + t[t[k].rch].cnt;
    t[k].val = t[t[k].lch].val + t[t[k].rch].val;
    return k;
}
long long query(int k1, int l, int r, int k)
{
    if(l == r) return t[k1].val / t[k1].cnt * k;
    int rnk = t[t[k1].lch].cnt;
    long long res = 0;
    int mid = (l + r) >> 1;
    if(k <= rnk)
    {
        res += query(t[k1].lch, l, mid, k);
    }
    else
    {
        res += t[t[k1].lch].val;
        res += query(t[k1].rch, mid + 1, r, k - rnk);
    }
    return res;
}
int main()
{
    freopen("in.in", "r", stdin);
    scanf("%d%d", &m, &n);
    for(int i = 1; i <= m; i++)
    {
        int s, e, p;
        scanf("%d%d%d", &s, &e, &p);
        q[i * 2 - 1].x = s;
        q[i * 2 - 1].v = p;
        q[i * 2].x = e + 1;
        q[i * 2].v = -p;
        b[i] = p;
    }
    std::sort(b + 1, b + 1 + m);
    int len = std::unique(b + 1, b + 1 + m) - (b + 1);
    std::sort(q + 1, q + 1 + 2 * m, cmp);
    rt[0] = build(1, len);
    int last = 1;
    for(int i = 1; i <= 2 * m; i++)
    {
        int p = std::lower_bound(b + 1, b + 1 + len, std::abs(q[i].v)) - b;
        int x = q[i].x;
        while(last < x)
        {
            rt[last + 1] = rt[last];
            last++;
        }
        if(x == T + 1) break;
        rt[last] = insert(rt[last], 1, len, p, (q[i].v > 0) ? 1 : -1);
    }
    long long pre = 1;
    for(int i = 1; i <= n; i++)
    {
        int x, a, b, c;
        scanf("%d%d%d%d", &x, &a, &b, &c);
        int k = 1 + (1ll * a * pre + 1ll * b) % c;
        if(k >= t[rt[x]].cnt) pre = t[rt[x]].val;
        else pre = query(rt[x], 1, len, k);
        printf("%lld\n", pre);
    }
    return 0;
}
