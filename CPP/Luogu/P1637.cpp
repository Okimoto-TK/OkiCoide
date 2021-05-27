#include <stdio.h>
#include <algorithm>
#include <map>
using namespace std;
int n, p;
long long a[30007];
long long _a[30007];
int b[30007];
int tree[120007];
map<long long, int> to;
int ans1[30007];
int ans2[30007];
void build(int k, int l, int r)
{
    if(l == r)
    {
        tree[k] = 0;
        return;
    }
    int mid = (l + r) >> 1;
    build(k << 1, l, mid);
    build(k << 1 | 1, mid + 1, r);
    tree[k] = tree[k << 1] + tree[k << 1 | 1];
}
void change(int k, int l, int r, int x)
{
    if(l == r)
    {
        tree[k] += 1;
        return;
    }
    int mid = (l + r) >> 1;
    if(x <= mid)
    {
        change(k << 1, l, mid, x);
    }
    else
    {
        change(k << 1 | 1, mid + 1, r, x);
    }
    tree[k] = tree[k << 1] + tree[k << 1 | 1];
}
int query(int k, int l, int r, int x, int y)
{
    if(x <= l && r <= y)
    {
        return tree[k];
    }
    int mid = (l + r) >> 1;
    int res = 0;
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
    for(int i = 1; i <= n; i++){
        scanf("%lld", &a[i]);
        _a[i] = a[i];
    }
    sort(_a + 1, _a + 1 + n);
    p = 1;
    for(int i = 1; i <= n; i++)
    {
        if(to[_a[i]] == 0)
        {
            to[_a[i]] = ++p;
        }
    }
    for(int i = 1; i <= n; i++)
    {
        b[i] = to[a[i]];
    }
    build(1, 1, p);
    for(int i = 1; i <= n; i++)
    {
        ans1[i] = query(1, 1, p, 1, b[i] - 1);
        change(1, 1, p, b[i]);
    }
    build(1, 1, p);
    for(int i = n; i >= 1; i--)
    {
        ans2[i] = query(1, 1, p, b[i] + 1, p);
        change(1, 1, p, b[i]);
    }
    long long ans = 0;
    for(int i = 1; i <= n; i++)
    {
        ans += ans1[i] * ans2[i];
    }
    printf("%lld", ans);
    return 0;
}
