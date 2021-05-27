#include <stdio.h>
#include <math.h>
#include <algorithm>
#include <ctype.h>
using namespace std;
inline int read()
{
    int X=0,w=0; char ch=0;
    while(!isdigit(ch)) {w|=ch=='-';ch=getchar();}
    while(isdigit(ch)) X=(X<<3)+(X<<1)+(ch^48),ch=getchar();
    return w?-X:X;
}
void write(int a)
{
    if(a<0) putchar('-'),a=-a;
    if(a>=10)write(a/10);
    putchar(a%10+48);
}
int n, m, blocksize;
int a[100007];
int t[100007];
struct query
{
    int l;
    int r;
    int a;
    int b;
    int id;
    int bl;
} q[1000007];
bool cmp(query a, query b)
{
    if(a.bl != b.bl)
    {
        return a.bl < b.bl;
    }
    return a.bl & 1 ? a.r < b.r : a.r > b.r;
}
int cnt[100007];
int ans[1000007];
inline int lowbit(int x)
{
    return x & (-x);
}
inline void change(int i, int k)
{
    for(; i <= n; i += lowbit(i))
    {
        t[i] += k;
    }
}
inline int query(int i)
{
    int res = 0;
    for(; i; i -= lowbit(i))
    {
        res += t[i];
    }
    return res;
}
inline void add(int x)
{
    int v = a[x];
    if(cnt[v]++ == 0)
    {
        change(v, 1);
    }
}
inline void del(int x)
{
    int v = a[x];
    if(--cnt[v] == 0)
    {
        change(v, -1);
    }
}
int main()
{
    scanf("%d%d", &n, &m);
    blocksize = 2 * sqrt(n);
    for(int i = 1; i <= n; i++)
    {
        a[i] = read();
    }
    for(int i = 1; i <= m; i++)
    {
        q[i].l = read();
        q[i].r = read();
        q[i].a = read();
        q[i].b = read();
        q[i].id = i;
        q[i].bl = (q[i].l - 1) / blocksize + 1;
    }
    sort(q + 1, q + 1 + m, cmp);
    int l = 1;
    int r = 0;
    for(int i = 1; i <= m; i++)
    {
        int ll = q[i].l;
        int rr = q[i].r;
        while(r < rr)
        {
            add(++r);
        }
        while(l > ll)
        {
            add(--l);
        }
        while(r > rr)
        {
            del(r--);
        }
        while(l < ll)
        {
            del(l++);
        }
        ans[q[i].id] = query(q[i].b) - query(q[i].a - 1);
    }
    for(int i = 1; i <= m; i++)
    {
        write(ans[i]);
        putchar('\n');
    }
    return 0;
}
