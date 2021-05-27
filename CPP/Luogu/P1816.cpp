#include <stdio.h>
#include <algorithm>
#define N 100007
using namespace std;
int n, m;
int a[N];
struct node
{
    int v;
    int i;
    node()
    {
        v = i = 1 << 30;
    }
} t[N << 2];
node merge(node l, node r)
{
    node res;
    if(l.v < r.v)
    {
        res.v = l.v;
        res.i = l.i;
    }
    else
    {
        res.v = r.v;
        res.i = r.i;
    }
    return res;
}
void build(int k, int l, int r)
{
    if(l == r)
    {
        t[k].v = a[l];
        t[k].i = l;
        return;
    }
    int mid = (l + r) >> 1;
    build(k << 1, l, mid);
    build(k << 1 | 1, mid + 1, r);
    t[k] = merge(t[k << 1], t[k << 1 | 1]);
}
node query(int k, int l, int r, int x, int y)
{
    if(x <= l && r <= y)
    {
        return t[k];
    }
    int mid = (l + r) >> 1;
    node res;
    if(x <= mid)
    {
        res = merge(res, query(k << 1, l, mid, x, y));
    }
    if(y > mid)
    {
        res = merge(res, query(k << 1 | 1, mid + 1, r, x, y));
    }
    return res;
}
int main()
{
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= n; i++)
    {
        scanf("%d", &a[i]);
    }
    build(1, 1, n);
    for(int i = 1; i <= m; i++)
    {
        int a, b;
        scanf("%d%d", &a, &b);
        printf("%d ", query(1, 1, n, a, b).v);
    }
    return 0;
}
