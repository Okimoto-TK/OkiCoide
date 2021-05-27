#include <cstdio>
#include <algorithm>
#include <queue>
#define N 300007
int n, k;
int c[N];
int t[N << 2];
int ti[N << 2];
void push_up(int k)
{
    if(t[k << 1] > t[k << 1 | 1])
    {
        t[k] = t[k << 1];
        ti[k] = ti[k << 1];
    }
    else
    {
        t[k] = t[k << 1 | 1];
        ti[k] = ti[k << 1 | 1];
    }
}
void build(int k, int l, int r)
{
    if(l == r)
    {
        t[k] = c[l];
        ti[k] = l;
        return;
    }
    int mid = (l + r) >> 1;
    build(k << 1, l, mid);
    build(k << 1 | 1, mid + 1, r);
    push_up(k);
}
void del(int k, int l, int r, int x)
{
    if(l == r)
    {
        t[k] = -1;
        return;
    }
    int mid = (l + r) >> 1;
    if(x <= mid) del(k << 1, l, mid, x);
    else del(k << 1 | 1, mid + 1, r, x);
    push_up(k);
}
std::pair<int, int> getMax(int k, int l, int r, int x, int y)
{
    if(x <= l && r <= y)
    {
        return std::make_pair(t[k], ti[k]);
    }
    int mid = (l + r) >> 1;
    int res = 0;
    int max = 0;
    if(x <= mid)
    {
        std::pair<int, int> _r = getMax(k << 1, l, mid, x, y);
        if(_r.first > max)
        {
            max = _r.first;
            res = _r.second;
        }
    }
    if(y > mid)
    {
        std::pair<int, int> _r = getMax(k << 1 | 1, mid + 1, r, x, y);
        if(_r.first > max)
        {
            max = _r.first;
            res = _r.second;
        }
    }
    return std::make_pair(max, res);
}
int sch[N];
int main()
{
    scanf("%d%d", &n, &k);
    for(int i = 1; i <= n; i++) scanf("%d", &c[i]);
    build(1, 1, n);
    long long ans = 0;
    for(int i = k + 1; i <= k + n; i++)
    {
        std::pair<int, int> r = getMax(1, 1, n, 1, std::min(i, n));
        ans += 1ll * r.first * (i - r.second);
        del(1, 1, n, r.second);
        sch[r.second] = i;
        //printf("%d", i);
    }
    printf("%lld\n", ans);
    for(int i = 1; i <= n; i++) printf("%d ", sch[i]);
    return 0;
}
