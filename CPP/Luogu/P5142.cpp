#include <stdio.h>
using namespace std;
int n, m;
long long a[100007];
long long lazy_tag[400007];
long long tree_pln[400007];
long long tree_sqr[400007];
void build(int k, int l, int r)
{
    if(l == r)
    {
        tree_pln[k] = a[l] % 1000000007;
        tree_sqr[k] = a[l] * a[l] % 1000000007;
        return;
    }
    int mid = (l + r) >> 1;
    build(k << 1, l, mid);
    build(k << 1 | 1, mid + 1, r);
    tree_pln[k] = (tree_pln[k << 1] + tree_pln[k << 1 | 1]) % 1000000007;
    tree_sqr[k] = (tree_sqr[k << 1] + tree_sqr[k << 1 | 1]) % 1000000007;
}
void change(int k, int l, int r, int x, long long v)
{
    if(l == r)
    {
        tree_pln[k] = v % 1000000007;
        tree_sqr[k] = v * v % 1000000007;
        return;
    }
    int mid = (l + r) >> 1;
    if(x <= mid)
    {
        change(k << 1, l, mid, x, v);
    }
    if(x > mid)
    {
        change(k << 1 | 1, mid + 1, r, x, v);
    }
    tree_pln[k] = (tree_pln[k << 1] + tree_pln[k << 1 | 1]) % 1000000007;
    tree_sqr[k] = (tree_sqr[k << 1] + tree_sqr[k << 1 | 1]) % 1000000007;
}
long long query_pln(int k, int l, int r, int x, int y)
{
    if(x <= l && r <= y)
    {
        return tree_pln[k] % 1000000007;
    }
    int mid = (l + r) >> 1;
    long long res = 0;
    if(x <= mid)
    {
        (res += query_pln(k << 1, l, mid, x, y)) %= 1000000007;
    }
    if(y > mid)
    {
        (res += query_pln(k << 1 | 1, mid + 1, r, x, y)) %= 1000000007;
    }
    return res % 1000000007;
}
long long query_sqr(int k, int l, int r, int x, int y)
{
    if(x <= l && r <= y)
    {
        return tree_sqr[k] % 1000000007;
    }
    int mid = (l + r) >> 1;
    long long res = 0;
    if(x <= mid)
    {
        (res += query_sqr(k << 1, l, mid, x, y)) %= 1000000007;
    }
    if(y > mid)
    {
        (res += query_sqr(k << 1 | 1, mid + 1, r, x, y)) %= 1000000007;
    }
    return res % 1000000007;
}
long long power(long long x, int k, long long p)
{
    long long r = 1;
    while(k)
    {
        if(k & 1)
        {
            (r *= x) %= p;
        }
        (x *= x) %= p;
        k >>= 1;
    }
    return r;
}
long long inv(long long x)
{
    return power(x, 1000000005, 1000000007);
}
int main()
{
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= n; i++)
    {
        scanf("%lld", &a[i]);
    }
    build(1, 1, n);
    for(int i = 1; i <= m; i++)
    {
        int opt;
        scanf("%d", &opt);
        if(opt == 1)
        {
            int x;
            long long k;
            scanf("%d%lld", &x, &k);
            change(1, 1, n, x, k);
        }
        else
        {
            int x, y;
            scanf("%d%d", &x, &y);
            long long ivr = inv(y - x + 1);
            long long pln = query_pln(1, 1, n, x, y) % 1000000007;
            long long ans = (query_sqr(1, 1, n, x, y) % 1000000007 - pln * pln % 1000000007 * ivr % 1000000007 + 1000000007) % 1000000007;
            (((ans *= ivr) %= 1000000007) += 1000000007) %= 1000000007;
            printf("%lld\n", ans);
        }
    }
    return 0;
}
