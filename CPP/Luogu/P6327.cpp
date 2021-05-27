#include <stdio.h>
#include <math.h>
using namespace std;
int n, m;
int a[200007];
double tree_sin[800007];
double tree_cos[800007];
double lazy_sin[800007];
double lazy_cos[800007];
void build(int k, int l, int r)
{
    lazy_sin[k] = 0;
    lazy_cos[k] = 1;
    if(l == r)
    {
        tree_sin[k] = sin(a[l]);
        tree_cos[k] = cos(a[l]);
        return;
    }
    int mid = (l + r) >> 1;
    build(k << 1, l, mid);
    build(k << 1 | 1, mid + 1, r);
    tree_sin[k] = tree_sin[k << 1] + tree_sin[k << 1 | 1];
    tree_cos[k] = tree_cos[k << 1] + tree_cos[k << 1 | 1];
}
void add(int k, int l, int r, double _sin, double _cos)
{
    double lazy_sbf = lazy_sin[k];
    double lazy_cbf = lazy_cos[k];
    double tree_sbf = tree_sin[k];
    double tree_cbf = tree_cos[k];
    tree_sin[k] = _cos * tree_sbf + _sin * tree_cbf;
    tree_cos[k] = _cos * tree_cbf - _sin * tree_sbf;
    lazy_sin[k] = _cos * lazy_sbf + _sin * lazy_cbf;
    lazy_cos[k] = _cos * lazy_cbf - _sin * lazy_sbf;
}
void push_down(int k, int l, int r)
{
    if(lazy_sin[k] == 0 && lazy_cos[k] == 1)
    {
        return;
    }
    int mid = (l + r) >> 1;
    add(k << 1, l, mid, lazy_sin[k], lazy_cos[k]);
    add(k << 1 | 1, mid + 1, r, lazy_sin[k], lazy_cos[k]);
    lazy_sin[k] = 0;
    lazy_cos[k] = 1;
}
void change(int k, int l, int r, int x, int y, double _sin, double _cos)
{
    if(x <= l && r <= y)
    {
        return add(k, l, r, _sin, _cos);
    }
    push_down(k, l, r);
    int mid = (l + r) >> 1;
    if(x <= mid)
    {
        change(k << 1, l, mid, x, y, _sin, _cos);
    }
    if(y > mid)
    {
        change(k << 1 | 1, mid + 1, r, x, y, _sin, _cos);
    }
    tree_sin[k] = tree_sin[k << 1] + tree_sin[k << 1 | 1];
    tree_cos[k] = tree_cos[k << 1] + tree_cos[k << 1 | 1];
}
double query(int k, int l, int r, int x, int y)
{
    if(x <= l && r <= y)
    {
        return tree_sin[k];
    }
    push_down(k, l, r);
    int mid = (l + r) >> 1;
    double res = 0;
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
        scanf("%d", &a[i]);
    }
    build(1, 1, n);
    scanf("%d", &m);
    for(int i = 1; i <= m; i++)
    {
        int opt;
        scanf("%d", &opt);
        if(opt == 1)
        {
            int l, r, v;
            scanf("%d%d%d", &l, &r, &v);
            change(1, 1, n, l, r, sin(v), cos(v));
        }
        else
        {
            int l, r;
            scanf("%d%d", &l, &r);
            printf("%.1lf\n", query(1, 1, n, l, r));
        }
    }
    return 0;
}
