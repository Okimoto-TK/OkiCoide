#include <stdio.h>
using namespace std;
int n, m;
double a[100007];
double lazy_tag[400007];
double tree_pln[400007];
double tree_sqr[400007];
void build(int k, int l, int r)
{
    if(l == r)
    {
        tree_pln[k] = a[l];
        tree_sqr[k] = a[l] * a[l];
        return;
    }
    int mid = (l + r) >> 1;
    build(k << 1, l, mid);
    build(k << 1 | 1, mid + 1, r);
    tree_pln[k] = tree_pln[k << 1] + tree_pln[k << 1 | 1];
    tree_sqr[k] = tree_sqr[k << 1] + tree_sqr[k << 1 | 1];
}
void add(int k, int l, int r, double v)
{
    tree_sqr[k] += 2 * tree_pln[k] * v + (r - l + 1) * v * v;
    tree_pln[k] += (r - l + 1) * v;
    lazy_tag[k] += v;
}
void push_down(int k, int l, int r)
{
    if(lazy_tag[k] == 0)
    {
        return;
    }
    int mid = (l + r) >> 1;
    add(k << 1, l, mid, lazy_tag[k]);
    add(k << 1 | 1, mid + 1, r, lazy_tag[k]);
    lazy_tag[k] = 0;
}
void change(int k, int l, int r, int x, int y, double v)
{
    if(x <= l && r <= y)
    {
        add(k, l, r, v);
        return;
    }
    push_down(k, l, r);
    int mid = (l + r) >> 1;
    if(x <= mid)
    {
        change(k << 1, l, mid, x, y, v);
    }
    if(y > mid)
    {
        change(k << 1 | 1, mid + 1, r, x, y, v);
    }
    tree_pln[k] = tree_pln[k << 1] + tree_pln[k << 1 | 1];
    tree_sqr[k] = tree_sqr[k << 1] + tree_sqr[k << 1 | 1];
}
double query_pln(int k, int l, int r, int x, int y)
{
    if(x <= l && r <= y)
    {
        return tree_pln[k];
    }
    push_down(k, l, r);
    int mid = (l + r) >> 1;
    double res = 0;
    if(x <= mid)
    {
        res += query_pln(k << 1, l, mid, x, y);
    }
    if(y > mid)
    {
        res += query_pln(k << 1 | 1, mid + 1, r, x, y);
    }
    return res;
}
double query_sqr(int k, int l, int r, int x, int y)
{
    if(x <= l && r <= y)
    {
        return tree_sqr[k];
    }
    push_down(k, l, r);
    int mid = (l + r) >> 1;
    double res = 0;
    if(x <= mid)
    {
        res += query_sqr(k << 1, l, mid, x, y);
    }
    if(y > mid)
    {
        res += query_sqr(k << 1 | 1, mid + 1, r, x, y);
    }
    return res;
}
int main()
{
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= n; i++)
    {
        scanf("%lf", &a[i]);
    }
    build(1, 1, n);
    for(int i = 1; i <= m; i++)
    {
        int opt;
        scanf("%d", &opt);
        if(opt == 1)
        {
            int x, y;
            double k;
            scanf("%d%d%lf", &x, &y, &k);
            change(1, 1, n, x, y, k);
        }
        else if(opt == 2)
        {
            int x, y;
            scanf("%d%d", &x, &y);
            printf("%.4lf\n", double(query_pln(1, 1, n, x, y)) / double(y - x + 1));
        }
        else
        {
            int x, y;
            scanf("%d%d", &x, &y);
            double pln = query_pln(1, 1, n, x, y);
            double ans = query_sqr(1, 1, n, x, y) - pln * pln / double(y - x + 1);
            ans /= double(y - x + 1);
            printf("%.4lf\n", ans);
        }
    }
    return 0;
}
