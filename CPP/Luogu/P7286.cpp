#include <stdio.h>
#include <algorithm>
using namespace std;
struct node
{
    long long id;
    long long vl;
};
int n;
node a[1000007];
long long t[4000007];
long long ans = 0;
bool cmp(node a, node b)
{
    return a.vl > b.vl;
}
void con(int k, int l, int r)
{
    if(l == r)
    {
        t[k] = a[l].id;
        return;
    }
    int mid = (l + r) >> 1;
    con(k << 1, l, mid);
    con((k << 1) | 1, mid + 1, r);
    t[k] = max(t[k << 1], t[(k << 1) | 1]);
}
int req(int k, int l, int r, int x, int y)
{
    if(x <= l && y >= r)
    {
        return t[k];
    }
    int mid = (l + r) >> 1;
    int res = 0;
    if(x <= mid)
    {
        res = max(res, req(k << 1, l, mid, x, y));
    }
    if(y > mid)
    {
        res = max(res, req((k << 1) | 1, mid + 1, r, x, y));
    }
    return res;
}
int main()
{
    scanf("%d", &n);
    for(int i = 1; i <= n; i++)
    {
        scanf("%lld", &a[i].vl);
        a[i].id = i;
    }
    sort(a + 1, a + 1 + n, cmp);
    con(1, 1, n);
    for(int i = 1; i <= n; i++)
    {
        ans = max(ans, a[i].vl * a[i].id);
        if(i != 1)ans = max(ans, a[i].vl * (a[i].id + req(1, 1, n, 1, i - 1)));
    }
    printf("%lld", ans);
    return 0;
}
