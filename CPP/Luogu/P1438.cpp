#include <stdio.h>
using namespace std;
long long n, m;
long long a[100007];
long long tree[400007];
long long lazy[400007];
void build(long long k, long long l, long long r)
{
    if(l == r)
    {
        tree[k] = a[l];
        return;
    }
    long long mid = (l + r) >> 1;
    build(k << 1, l, mid);
    build(k << 1 | 1, mid + 1, r);
    tree[k] = tree[k << 1] + tree[k << 1 | 1];
}
void add(long long k, long long l, long long r, long long v)
{
    tree[k] += (r - l + 1) * v;
    lazy[k] += v;
}
void push_down(long long k, long long l, long long r)
{
    if(lazy[k] == 0)
    {
        return;
    }
    long long mid = (l + r) >> 1;
    add(k << 1, l, mid, lazy[k]);
    add(k << 1 | 1, mid + 1, r, lazy[k]);
    lazy[k] = 0;
}
void change(long long k, long long l, long long r, long long x, long long y, long long v)
{
    if(x <= l && r <= y)
    {
        add(k, l, r, v);
        return;
    }
    push_down(k, l, r);
    long long mid = (l + r) >> 1;
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
long long query(long long k, long long l, long long r, long long x, long long y)
{
    if(x <= l && r <= y)
    {
        return tree[k];
    }
    push_down(k, l, r);
    long long mid = (l + r) >> 1;
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
int main()
{
    scanf("%lld%lld", &n, &m);
    long long last = 0;
    long long t;
    for(long long i = 1; i <= n; i++)
    {
        scanf("%lld", &t);
        a[i] = t - last;
        last = t;
    }
    build(1, 1, n);
    for(long long i = 1; i <= m; i++)
    {
        long long opt;
        scanf("%lld", &opt);
        if(opt == 1)
        {
            long long l, r, K, D;
            scanf("%lld%lld%lld%lld", &l, &r, &K, &D);
            change(1, 1, n, l, l, K);
            if(r + 1 <= n)
            {
                change(1, 1, n, r + 1, r + 1, -1 * (K + (r - l) * D));
            }
            if(l + 1 <= n && l + 1 <= r)
            {
                change(1, 1, n, l + 1, r, D);
            }
        }
        else
        {
            long long p;
            scanf("%lld", &p);
            printf("%lld\n", query(1, 1, n, 1, p));
        }
    }
    return 0;
}
