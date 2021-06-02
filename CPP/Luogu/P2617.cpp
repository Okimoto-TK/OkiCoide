#include <cstdio>
#include <algorithm>
#define N 100007
int n, m, pool;
int a[N];
int rt[N];
struct Node
{
    int lch;
    int rch;
    int cnt;
    Node() { lch = rch = cnt = 0; }
} t[40000000];
struct Req
{
    int opt;
    int l, r, k;
    int x, y;
} req[N];
int num[2 * N];
int nsiz, len;
void change(int &k, int l, int r, int x, int v)
{
    if(k == 0) k = ++pool;
    t[k].cnt += v;
    if(l == r) return;
    int mid = (l + r) >> 1;
    if(x <= mid) change(t[k].lch, l, mid, x, v);
    else change(t[k].rch, mid + 1, r, x, v);
}
int kbuf[2][100];
int cnt[2];
int lowbit(int x) { return x & (-x); }
void update(int x, int v)
{
    int k = std::lower_bound(num + 1, num + 1 + len, a[x]) - num;
    for(; x <= n; x += lowbit(x))
    {
        change(rt[x], 1, len, k, v);
    }
}
int getKth(int l, int r, int k)
{
    if(l == r) return l;
    int val = 0;
    for(int i = 1; i <= cnt[0]; i++) val += t[t[kbuf[0][i]].lch].cnt;
    for(int i = 1; i <= cnt[1]; i++) val -= t[t[kbuf[1][i]].lch].cnt;
    int mid = (l + r) >> 1;
    if(k <= val)
    {
        for(int i = 1; i <= cnt[0]; i++) kbuf[0][i] = t[kbuf[0][i]].lch;
        for(int i = 1; i <= cnt[1]; i++) kbuf[1][i] = t[kbuf[1][i]].lch;
        return getKth(l, mid, k);
    }
    else
    {
        for(int i = 1; i <= cnt[0]; i++) kbuf[0][i] = t[kbuf[0][i]].rch;
        for(int i = 1; i <= cnt[1]; i++) kbuf[1][i] = t[kbuf[1][i]].rch;
        return getKth(mid + 1, r, k - val);
    }
}
int query(int l, int r, int k)
{
    l--;
    cnt[0] = cnt[1] = 0;
    for(; r != 0; r -= lowbit(r)) kbuf[0][++cnt[0]] = rt[r];
    for(; l != 0; l -= lowbit(l)) kbuf[1][++cnt[1]] = rt[l];
    return getKth(1, len, k);
}
int main()
{
    //freopen("in.in", "r", stdin);
    scanf("%d%d", &n, &m);
    rt[0] = ++pool;
    for(int i = 1; i <= n; i++)
    {
        scanf("%d", &a[i]);
        num[++nsiz] = a[i];
    }
    for(int i = 1; i <= m; i++)
    {
        char opt[2];
        scanf("%s", opt);
        if(opt[0] == 'C')
        {
            req[i].opt = 0;
            scanf("%d%d", &req[i].x, &req[i].y);
            num[++nsiz] = req[i].y; 
        }
        else
        {
            req[i].opt = 1;
            scanf("%d%d%d", &req[i].l, &req[i].r, &req[i].k);
        }
    }
    std::sort(num + 1, num + 1 + nsiz);
    len = std::unique(num + 1, num + 1 + nsiz) - (num + 1);
    for(int i = 1; i <= n; i++) update(i, 1);
    for(int i = 1; i <= m; i++)
    {
        if(req[i].opt == 0)
        {
            update(req[i].x, -1);
            a[req[i].x] = req[i].y;
            update(req[i].x, 1);
        }
        else printf("%d\n", num[query(req[i].l, req[i].r, req[i].k)]);
    }
    return 0;
}
