#include <cstdio>
#include <algorithm>
#define N 100007
int n, c, f, pool;
struct Item
{
    int val;
    int scr;
} a[N];
int _a[N];
int rt[N];
struct Node
{
    int lch;
    int rch;
    int val;
    Node() { lch = rch = val = 0; }
} min[8000000];
bool cmp(Item a, Item b)
{
    return a.scr < b.scr;
}
long long f1[N];
long long f2[N];
int build(int l, int r)
{
    int k = ++pool;
    if(l == r) return k;
    int mid = (l + r) >> 1;
    min[k].lch = build(l, mid);
    min[k].rch = build(mid + 1, r);
    min[k].val = min[min[k].lch].val + min[min[k].rch].val;
    return k;
}
int insert(int _k, int l, int r, int x, int v)
{
    int k = ++pool;
    if(l == r)
    {
        min[k].val = min[_k].val + v;
        return k;
    }
    int mid = (l + r) >> 1;
    min[k].lch = min[_k].lch;
    min[k].rch = min[_k].rch;
    if(x <= mid) min[k].lch = insert(min[k].lch, l, mid, x, v);
    else min[k].rch = insert(min[k].rch, mid + 1, r, x, v);
    min[k].val = min[min[k].lch].val + min[min[k].rch].val;
    return k;
}
int getKth(int k1, int k2, int l, int r, int k)
{
    if(l == r) return l;
    int mid = (l + r) >> 1;
    if(k <= min[min[k1].lch].val - min[min[k2].lch].val) return getKth(min[k1].lch, min[k2].lch, l, mid, k);
    else return getKth(min[k1].rch, min[k2].rch, mid + 1, r, k - (min[min[k1].lch].val - min[min[k2].lch].val));
}
int main()
{
    //freopen("in.in", "r", stdin);
    scanf("%d%d%d", &n, &c, &f);
    for(int i = 1; i <= c; i++)
    {
        scanf("%d%d", &a[i].scr, &a[i].val);
        _a[i] = a[i].val;
    }
    std::sort(a + 1, a + 1 + c, cmp);
    std::sort(_a + 1, _a + 1 + c);
    int len = std::unique(_a + 1, _a + 1 + c) - _a - 1;
    rt[0] = build(1, len);
    for(int i = 1; i <= c; i++)
    {
        a[i].val = std::lower_bound(_a + 1, _a + 1 + len, a[i].val) - _a;
        rt[i] = insert(rt[i - 1], 1, len, a[i].val, 1);
    }
    int l = n / 2;
    for(int i = 1; i <= l; i++) f1[i] = f1[i - 1] + _a[a[i].val];
    for(int i = c; i > c - l; i--) f2[i] = f2[i + 1] + _a[a[i].val];
    for(int i = l + 1; i <= c; i++)
    {
        f1[i] = f1[i - 1] + std::min(0, _a[a[i].val] - _a[getKth(rt[i - 1], rt[0], 1, len, l)]);
    }
    for(int i = c - l; i >= 1; i--)
    {
        f2[i] = f2[i + 1] + std::min(0, _a[a[i].val] - _a[getKth(rt[c], rt[i], 1, len, l)]);
    }
    for(int i = c - l; i >= l + 1; i--)
    {
        if(f1[i - 1] + f2[i + 1] + _a[a[i].val] <= f)
        {
            printf("%d\n", a[i].scr);
            return 0;
        }
    }
    printf("-1\n");
    return 0;
}
