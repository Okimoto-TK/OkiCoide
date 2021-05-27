#include <stdio.h>
#include <algorithm>
using namespace std;
int n, m;
int a[800007];
int tree[800007];
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
    tree[k] = max(tree[k << 1], tree[k << 1 | 1]);
}
int query(int k, int l, int r, int x, int y)
{
    if(l >= x && r <= y)
    {
        return tree[k];
    }
    int res = 0;
    int mid = (l + r) >> 1;
    if(x <= mid)
    {
        res = max(res, query(k << 1, l, mid, x, y));
    }
    if(y > mid)
    {
        res = max(res, query(k << 1 | 1, mid + 1, r, x, y));
    }
    return res;
}
void change(int k, int l, int r, int x, int v)
{
    if(l == r)
    {
        tree[k] = v;
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
    tree[k] = max(tree[k << 1], tree[k << 1 | 1]);
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
        char c[2];
        int a, b;
        scanf("%s%d%d", c, &a, &b);
        if(c[0] == 'Q')
        {
            printf("%d\n", query(1, 1, n, a, b));
        }
        else
        {
            int _a = query(1, 1, n, a, a);
            if(_a < b)
            {
                change(1, 1, n, a, b);
            }
        }
    }
    return 0;
}
