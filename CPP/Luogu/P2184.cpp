#include <stdio.h>
#include <algorithm>
using namespace std;
int n, m;
int tree_bgn[400007];
int tree_end[400007];
void change_bgn(int k, int l, int r, int x)
{
    if(l == r)
    {
        tree_bgn[k] += 1;
        return;
    }
    int mid = (l + r) >> 1;
    if(x <= mid)
    {
        change_bgn(k << 1, l, mid, x);
    }
    if(x > mid)
    {
        change_bgn(k << 1 | 1, mid + 1, r, x);
    }
    tree_bgn[k] = tree_bgn[k << 1] + tree_bgn[k << 1 | 1];
}
void change_end(int k, int l, int r, int x)
{
    if(l == r)
    {
        tree_end[k] += 1;
        return;
    }
    int mid = (l + r) >> 1;
    if(x <= mid)
    {
        change_end(k << 1, l, mid, x);
    }
    if(x > mid)
    {
        change_end(k << 1 | 1, mid + 1, r, x);
    }
    tree_end[k] = tree_end[k << 1] + tree_end[k << 1 | 1];
}
int query_bgn(int k, int l, int r, int x, int y)
{
    if(x <= l && r <= y)
    {
        return tree_bgn[k];
    }
    int mid = (l + r) >> 1;
    int res = 0;
    if(x <= mid)
    {
        res += query_bgn(k << 1, l, mid, x, y);
    }
    if(y > mid)
    {
        res += query_bgn(k << 1 | 1, mid + 1, r, x, y);
    }
    return res;
}
int query_end(int k, int l, int r, int x, int y)
{
    if(x <= l && r <= y)
    {
        return tree_end[k];
    }
    int mid = (l + r) >> 1;
    int res = 0;
    if(x <= mid)
    {
        res += query_end(k << 1, l, mid, x, y);
    }
    if(y > mid)
    {
        res += query_end(k << 1 | 1, mid + 1, r, x, y);
    }
    return res;
}
int main()
{
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= m; i++)
    {
        int q, l, r;
        scanf("%d%d%d", &q, &l, &r);
        if(q == 1)
        {
            change_bgn(1, 1, n, l);
            change_end(1, 1, n, r + 1);
        }
        else
        {
            printf("%d\n", query_bgn(1, 1, n, 1, r) - query_end(1, 1, n, 1, l));
        }
    }
    return 0;
}
