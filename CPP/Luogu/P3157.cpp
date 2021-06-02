#include <cstdio>
#define N 100005
int n, m, pool;
int a[N];
int pos[N];
int rt[N];
struct Node
{
    int lch, rch;
    int cnt;
    Node() { lch = rch = cnt = 0; }
} t[10000000];
int lowbit(int x) { return (x & -x); }
void change(int &k, int l, int r, int x, int v)
{
    if(k == 0) k = ++pool;
    t[k].cnt += v;
    if(l == r)
    {
        return;
    }
    int mid = (l + r) >> 1;
    if(x <= mid) change(t[k].lch, l, mid, x, v);
    else change(t[k].rch, mid + 1, r, x, v);
}
void update(int i, int v)
{
    int x = a[i];
    for(; i <= n; i += lowbit(i)) change(rt[i], 1, n, x, v);
}
int cnt[2];
int buf[2][100];
int diff()
{
    int res = 0;
    for(int i = 1; i <= cnt[1]; i++) res += t[t[buf[1][i]].rch].cnt;
    for(int i = 1; i <= cnt[0]; i++) res -= t[t[buf[0][i]].rch].cnt;
    return res;
}
int diffs()
{
    int res = 0;
    for(int i = 1; i <= cnt[1]; i++) res += t[t[buf[1][i]].lch].cnt;
    for(int i = 1; i <= cnt[0]; i++) res -= t[t[buf[0][i]].lch].cnt;
    return res;
}
int query(int l, int r, int x, bool grt)
{
    int mid = (l + r) >> 1;
    int res = 0;
    if(x > mid)
    {
        if(grt) res += diffs();
        for(int i = 1; i <= cnt[1]; i++) buf[1][i] = t[buf[1][i]].rch;
        for(int i = 1; i <= cnt[0]; i++) buf[0][i] = t[buf[0][i]].rch;
        if(l != r) res += query(mid + 1, r, x, grt);
    }
    else
    {
        if(!grt) res += diff();
        for(int i = 1; i <= cnt[1]; i++) buf[1][i] = t[buf[1][i]].lch;
        for(int i = 1; i <= cnt[0]; i++) buf[0][i] = t[buf[0][i]].lch;
        if(l != r) res += query(l, mid, x, grt);
    }
    return res;
}
int ask(int l, int r, int x, bool grt)
{
    cnt[0] = cnt[1] = 0;
    for(int i = l - 1; i != 0; i -= lowbit(i)) buf[0][++cnt[0]] = rt[i];
    for(int i = r; i != 0; i -= lowbit(i)) buf[1][++cnt[1]] = rt[i];
    return query(1, n, x, grt);
}
int ans[N];
int main()
{
    //freopen("in.in", "r", stdin);
    scanf("%d%d", &n, &m);
    long long sum = 0;
    for(int i = 1; i <= n; i++)
    {
        scanf("%d", &a[i]);
        pos[a[i]] = i;
        sum += ask(1, i - 1, a[i], false);
        //printf("%d\n", sum);
        update(i, 1);
    }
    printf("%lld\n", sum);
    for(int i = 1; i < m; i++)
    {
        int x;
        scanf("%d", &x);
        sum -= ask(1, pos[x] - 1, x, false);
        sum -= ask(pos[x] + 1, n, x, true);
        printf("%lld\n", sum);
        update(pos[x], -1);
    }
    return 0;
}
