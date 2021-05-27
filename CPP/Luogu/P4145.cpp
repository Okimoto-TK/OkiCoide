#include <stdio.h>
#include <math.h>
#include <algorithm>
using namespace std;
int n, m;
long long a[100007];
long long tree[400007];
void build(int k, int l, int r)
{
    if(l == r)
    {
        tree[k] = a[l];
        return;
    }
    int mid = (l + r) >> 1;
    build(k << 1, l, mid);
    build(k << 1 | 1, mid + 1, r);
    tree[k] = tree[k << 1] + tree[k << 1 | 1];
}
bool check(int k, int l, int r)
{
    return tree[k] != (r - l + 1);
}
void change(int k, int l, int r, int x, int y)
{
    if(l == r)
    {
        tree[k] = (long long)sqrt(tree[k]);
        return;
    }
    int mid = (l + r) >> 1;
    if(x <= mid && check(k << 1, l, mid))
    {
        change(k << 1, l, mid, x, y);
    }
    if(y > mid && check(k << 1 | 1, mid + 1, r))
    {
        change(k << 1 | 1, mid + 1, r, x, y);
    }
    tree[k] = tree[k << 1] + tree[k << 1 | 1];
}
long long query(int k, int l, int r, int x, int y)
{
    if(x <= l && r <= y)
    {
        return tree[k];
    }
    long long res = 0;
    int mid = (l + r) >> 1;
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
    scanf("%d", &n);
    for(int i = 1; i <= n; i++)
    {
        scanf("%lld", &a[i]);
    }
    build(1, 1, n);
    scanf("%d", &m);
    for(int i = 1; i <= m; i++)
    {
        int k, l, r;
        scanf("%d%d%d", &k, &l, &r);
        if(l > r)
        {
            swap(l, r);
        }
        if(k == 0)
        {
            change(1, 1, n, l, r);
        }
        else
        {
            printf("%lld\n", query(1, 1, n, l, r));
        }
    }
    return 0;
}
