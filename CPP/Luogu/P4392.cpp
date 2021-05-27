#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
int n, m, c;
int a[1000007];
int tmax[4000007];
int tmin[4000007];
void push_up(int k)
{
    tmax[k] = max(tmax[k << 1], tmax[k << 1 | 1]);
    tmin[k] = min(tmin[k << 1], tmin[k << 1 | 1]);
}
void change(int k, int l, int r, int x, int v)
{
    if(l == r)
    {
        tmax[k] = v;
        tmin[k] = v;
        return;
    }
    int mid = (l + r) >> 1;
    if(x <= mid)
    {
        change(k << 1, l, mid, x, v);
    }
    else
    {
        change(k << 1 | 1, mid + 1, r, x, v);
    }
    push_up(k);
}
int query_max(int k, int l, int r, int x, int y)
{
    if(x <= l && r <= y)
    {
        return tmax[k];
    }
    int mid = (l + r) >> 1;
    int res = -0x3f3f3f3f;
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
        return tmin[k];
    }
    int mid = (l + r) >> 1;
    int res = 0x3f3f3f3f;
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
    scanf("%d%d%d", &n, &m, &c);
    bool b = false;
    for(int i = 1; i <= n; i++)
    {
        scanf("%d", &a[i]);
        change(1, 1, n, i, a[i]);
        if(i - m + 1 < 1)
        {
            continue;
        }
        if(query_max(1, 1, n, i - m + 1, i) - query_min(1, 1, n, i - m + 1, i) <= c)
        {
            b = true;
            printf("%d\n", i - m + 1);
        }
    }
    if(!b)
    {
        printf("NONE");
    }
    return 0;
}
