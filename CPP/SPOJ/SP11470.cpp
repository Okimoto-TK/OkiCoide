#include <cstdio>
#include <algorithm>
#define N 100007
inline int read(){
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-')
            f=-1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9'){
        x=(x<<1)+(x<<3)+(ch^48);
        ch=getchar();
    }
    return x*f;
}
inline void write(long long x)
{
     if(x<0) putchar('-'),x=-x;
     if(x>9) write(x/10);
     putchar(x%10+'0');
}
int n, m, pool, now;
int a[N];
int rt[N];
struct Node
{
    int lazy;
    int lch;
    int rch;
    long long sum;
    Node() { lazy = lch = rch = sum = 0; }
} t[20000000];
int build(int l, int r)
{
    int k = ++pool;
    if(l == r)
    {
        t[k].sum = a[l];
        return k;
    }
    int mid = (l + r) >> 1;
    t[k].lch = build(l, mid);
    t[k].rch = build(mid + 1, r);
    t[k].sum = t[t[k].lch].sum + t[t[k].rch].sum;
    return k;
}
inline void add(int k, int l, int r, int v)
{
    t[k].lazy += v;
    t[k].sum += 1ll * (r - l + 1) * v;
}
int change(int _k, int l, int r, int x, int y, int v)
{
    int k = ++pool;
    t[k] = t[_k];
    if(x <= l && r <= y)
    {
        add(k, l, r, v);
        return k;
    }
    t[k].sum += 1ll * std::max(0, std::min(r, y) - std::max(l, x) + 1) * v;
    int mid = (l + r) >> 1;
    if(x <= mid) t[k].lch = change(t[_k].lch, l, mid, x, y, v);
    if(y > mid) t[k].rch = change(t[_k].rch, mid + 1, r, x, y, v);
    return k;
}
long long query(int k, int l, int r, int x, int y, int la)
{
    if(x <= l && r <= y) return t[k].sum + (r - l + 1) * la;
    int mid = (l + r) >> 1;
    long long res = 0;
    if(x <= mid) res += query(t[k].lch, l, mid, x, y, la + t[k].lazy);
    if(y > mid) res += query(t[k].rch, mid + 1, r, x, y, la + t[k].lazy);
    return res;
}
int main()
{
    //freopen("in.in", "r", stdin);
    scanf("%d%d", &n, &m);
    for(register int i = 1; i <= n; i++) a[i] = read();
    rt[0] = build(1, n);
    for(register int i = 1; i <= m; i++)
    {
        char opt[2];
        scanf("%s", opt);
        if(opt[0] == 'C')
        {
            int l = read(), r = read(), d = read();
            rt[now + 1] = change(rt[now], 1, n, l, r, d);
            now++;
        }
        else if(opt[0] == 'Q')
        {
            int l = read(), r = read();
            write(query(rt[now], 1, n, l, r, 0));
            putchar('\n');
        }
        else if(opt[0] == 'H')
        {
            int l = read(), r = read(), t = read();
            write(query(rt[t], 1, n, l, r, 0));
            putchar('\n');
        }
        else now = read();
    }
    return 0;
}
