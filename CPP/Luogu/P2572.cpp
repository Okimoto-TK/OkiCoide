#include <stdio.h>
#include <algorithm>
#define N 100007
using namespace std;
struct node
{
    int cnt0;
    int cnt1;
    int len0;
    int len1;
    int rlen0;
    int rlen1;
    int llen0;
    int llen1;
    int left;
    int right;
    node()
    {
        cnt0 = cnt1 = len0 = len1 = llen0 = llen1 = rlen0 = rlen1 = 0;
    }
};
int n, m;
int a[N];
int clr[N << 2];
bool flp[N << 2];
node t[N << 2];
void push_up(int k, int l, int r)
{
    int mid = (l + r) >> 1;
    int llen = mid - l + 1;
    int rlen = r - mid;
    t[k].left = t[k << 1].left;
    t[k].right = t[k << 1 | 1].right;
    t[k].len0 = max(t[k << 1].len0, t[k << 1 | 1].len0);
    t[k].len1 = max(t[k << 1].len1, t[k << 1 | 1].len1);
    t[k].llen1 = t[k << 1].llen1;
    t[k].llen0 = t[k << 1].llen0;
    t[k].rlen0 = t[k << 1 | 1].rlen0;
    t[k].rlen1 = t[k << 1 | 1].rlen1;
    t[k].cnt0 = t[k << 1 | 1].cnt0 + t[k << 1].cnt0;
    t[k].cnt1 = t[k << 1 | 1].cnt1 + t[k << 1].cnt1;
    if(t[k << 1].right == t[k << 1 | 1].left)
    {
        t[k].len0 = max(t[k].len0, t[k << 1].rlen0 + t[k << 1 | 1].llen0);
        t[k].len1 = max(t[k].len1, t[k << 1].rlen1 + t[k << 1 | 1].llen1);
        if(t[k << 1].llen0 == llen)
        {
            t[k].llen0 = t[k << 1 | 1].llen0 + llen;
        }
        if(t[k << 1].llen1 == llen)
        {
            t[k].llen1 = t[k << 1 | 1].llen1 + llen;
        }
        if(t[k << 1 | 1].rlen0 == rlen)
        {
            t[k].rlen0 = t[k << 1].rlen0 + rlen;
        }
        if(t[k << 1 | 1].rlen1 == rlen)
        {
            t[k].rlen1 = t[k << 1].rlen1 + rlen;
        }
    }
}
void build(int k, int l, int r)
{
    clr[k] = -1;
    if(l == r)
    {
        if(a[l] == 0)
        {
            t[k].cnt0 = 1;
            t[k].len0 = 1;
            t[k].llen0 = 1;
            t[k].rlen0 = 1;
            t[k].left = 0;
            t[k].right = 0;
        }
        else
        {
            t[k].cnt1 = 1;
            t[k].len1 = 1;
            t[k].llen1 = 1;
            t[k].rlen1 = 1;
            t[k].left = 1;
            t[k].right = 1;
        }
        return;
    }
    int mid = (l + r) >> 1;
    build(k << 1, l, mid);
    build(k << 1 | 1, mid + 1, r);
    push_up(k, l, r);
}
void cover(int k, int l, int r, int v)
{
    t[k].left = v;
    t[k].right = v;
    if(v == 0)
    {
        t[k].cnt0 = r - l + 1;
        t[k].cnt1 = 0;
        t[k].len0 = t[k].cnt0;
        t[k].len1 = 0;
        t[k].llen0 = t[k].cnt0;
        t[k].llen1 = 0;
        t[k].rlen0 = t[k].cnt0;
        t[k].rlen1 = 0;
    }
    else
    {
        t[k].cnt1 = r - l + 1;
        t[k].cnt0 = 0;
        t[k].len1 = t[k].cnt1;
        t[k].len0 = 0;
        t[k].llen1 = t[k].cnt1;
        t[k].llen0 = 0;
        t[k].rlen1 = t[k].cnt1;
        t[k].rlen0 = 0;
    }
    clr[k] = v;
    flp[k] = false;
}
void flip(int k, int l, int r)
{
    flp[k] ^= true;
    t[k].left ^= 1;
    t[k].right ^= 1;
    swap(t[k].cnt0, t[k].cnt1);
    swap(t[k].llen0, t[k].llen1);
    swap(t[k].rlen1, t[k].rlen0);
    swap(t[k].len0, t[k].len1);
}
void push_down(int k, int l, int r)
{
    int mid = (l + r) >> 1;
    if(clr[k] != -1)
    {
        cover(k << 1, l, mid, clr[k]);
        cover(k << 1 | 1, mid + 1, r, clr[k]);
        clr[k] = -1;
    }
    if(flp[k])
    {
        flip(k << 1, l, mid);
        flip(k << 1 | 1, mid + 1, r);
        flp[k] = false;
    }
}
void modify(int k, int l, int r, int x, int y, int v)
{
    push_down(k, l, r);
    if(x <= l && r <= y)
    {
        cover(k, l, r, v);
        return;
    }
    int mid = (l + r) >> 1;
    if(x <= mid)
    {
        modify(k << 1, l, mid, x, y, v);
    }
    if(y > mid)
    {
        modify(k << 1 | 1, mid + 1, r, x, y, v);
    }
    push_up(k, l, r);
}
void negate(int k, int l, int r, int x, int y)
{
    push_down(k, l, r);
    if(x <= l && r <= y)
    {
        flip(k, l, r);
        return;
    }
    int mid = (l + r) >> 1;
    if(x <= mid)
    {
        negate(k << 1, l, mid, x, y);
    }
    if(y > mid)
    {
        negate(k << 1 | 1, mid + 1, r, x, y);
    }
    push_up(k, l, r);
}
int query(int k, int l, int r, int x, int y)
{
    push_down(k, l, r);
    if(x <= l && r <= y)
    {
        return t[k].cnt1;
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
node merge(node a, node b, int llen, int rlen)
{
    node r;
    r.left = a.left;
    r.right = b.right;
    r.len0 = max(a.len0, b.len0);
    r.len1 = max(a.len1, b.len1);
    r.llen1 = a.llen1;
    r.llen0 = a.llen0;
    r.rlen0 = b.rlen0;
    r.rlen1 = b.rlen1;
    r.cnt0 = b.cnt0 + a.cnt0;
    r.cnt1 = b.cnt1 + a.cnt1;
    if(a.right == b.left)
    {
        r.len0 = max(r.len0, a.rlen0 + b.llen0);
        r.len1 = max(r.len1, a.rlen1 + b.llen1);
        if(a.llen0 == llen)
        {
            r.llen0 = b.llen0 + llen;
        }
        if(a.llen1 == llen)
        {
            r.llen1 = b.llen1 + llen;
        }
        if(b.rlen0 == rlen)
        {
            r.rlen0 = a.rlen0 + rlen;
        }
        if(b.rlen1 == rlen)
        {
            r.rlen1 = a.rlen1 + rlen;
        }
    }
    return r;
}
pair<node, int> query_ctn(int k, int l, int r, int x, int y)
{
    push_down(k, l, r);
    if(x <= l && r <= y)
    {
        return pair<node, int>(t[k], r - l + 1);
    }
    int mid = (l + r) >> 1;
    node res;
    if(x <= mid && y > mid)
    {
        pair<node, int> a = query_ctn(k << 1, l, mid, x, y);
        pair<node, int> b = query_ctn(k << 1 | 1, mid + 1, r, x, y);
        return pair<node, int>(merge(a.first, b.first, a.second, b.second), a.second + b.second);
    }
    if(x <= mid)
    {
        pair<node, int> a = query_ctn(k << 1, l, mid, x, y);
        return pair<node, int>(a.first, a.second);
    }
    else
    {
        pair<node, int> a = query_ctn(k << 1 | 1, mid + 1, r, x, y);
        return pair<node, int>(a.first, a.second);
    }
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
        int op, l, r;
        scanf("%d%d%d", &op, &l, &r);
        l++;
        r++;
        if(op == 0)
        {
            modify(1, 1, n, l, r, 0);
        }
        else if(op == 1)
        {
            modify(1, 1, n, l, r, 1);
        }
        else if(op == 2)
        {
            negate(1, 1, n, l, r);
        }
        else if(op == 3)
        {
            int res = query(1, 1, n, l, r);
            printf("%d\n", res);
        }
        else
        {
            int ans = query_ctn(1, 1, n, l, r).first.len1;
            printf("%d\n", ans);
        }
    }
    return 0;
}
