#include <stdio.h>
#include <algorithm>
#define N 50007
#define INF 1919810
using namespace std;
int n, q;
int h[N];
struct node
{
    int max;
    int min;
} t[4 * N];
void push_up(int k)
{
    t[k].max = max(t[k << 1].max, t[k << 1 | 1].max);
    t[k].min = min(t[k << 1].min, t[k << 1 | 1].min);
}
void build(int k, int l, int r)
{
    if(l == r)
    {
        t[k].max = t[k].min = h[l];
        return;
    }
    int mid = (l + r) >> 1;
    build(k << 1, l, mid);
    build(k << 1 | 1, mid + 1, r);
    push_up(k);
}
int query_max(int k, int l, int r, int x, int y)
{
    if(x <= l && r <= y)
    {
        return t[k].max;
    }
    int mid = (l + r) >> 1;
    int res = -INF;
    if(x <= mid)
    {
        res = max(res, query_max(k << 1, l, mid, x, y));
    }
    if(y > mid)
    {
        res = max(res, query_max(k << 1 | 1, mid + 1, r, x, y));
    }
    return res;
}
int query_min(int k, int l, int r, int x, int y)
{
    if(x <= l && r <= y)
    {
        return t[k].min;
    }
    int mid = (l + r) >> 1;
    int res = INF;
    if(x <= mid)
    {
        res = min(res, query_min(k << 1, l, mid, x, y));
    }
    if(y > mid)
    {
        res = min(res, query_min(k << 1 | 1, mid + 1, r, x, y));
    }
    return res;
}
int main()
{
    scanf("%d%d", &n, &q);
    for(int i = 1; i <= n; i++)
    {
        scanf("%d", &h[i]);
    }
    build(1, 1, n);
    for(int i = 1; i <= q; i++)
    {
        int a, b;
        scanf("%d%d", &a, &b);
        printf("%d\n", query_max(1, 1, n, a, b) - query_min(1, 1, n, a, b));
    }
    return 0;
}
