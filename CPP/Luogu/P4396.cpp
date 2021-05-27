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
int t2[100007];
int t1[100007];
struct query
{
    int l;
    int r;
    int a;
    int b;
    int id;
    int bl;
} q[100007];
bool cmp(query a, query b)
{
    if(a.bl != b.bl)
    {
        return a.bl < b.bl;
    }
    return a.bl & 1 ? a.r < b.r : a.r > b.r;
}
int cnt[100007];
int ans[100007];
int _ans[100007];
inline int lowbit(int x)
{
    return x & (-x);
}
inline void change1(int i, int k)
{
    for(; i <= 1e5; i += lowbit(i))
    {
        t1[i] += k;
    }
}
inline int query1(int i)
{
    int res = 0;
    for(; i; i -= lowbit(i))
    {
        res += t1[i];
    }
    return res;
}
inline void add1(int x)
{
    int v = a[x];
    change1(v, 1);
}
inline void del1(int x)
{
    int v = a[x];
    change1(v, -1);
}
inline void change2(int i, int k)
{
    for(; i <= 1e5; i += lowbit(i))
    {
        t2[i] += k;
    }
}
inline int query2(int i)
{
    int res = 0;
    for(; i; i -= lowbit(i))
    {
        res += t2[i];
    }
    return res;
}
inline void add2(int x)
{
    int v = a[x];
    if(cnt[v]++ == 0)
    {
        change2(v, 1);
    }
}
inline void del2(int x)
{
    int v = a[x];
    if(--cnt[v] == 0)
    {
        change2(v, -1);
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
            add1(++r);
            add2(r);
        }
        while(l > ll)
        {
            add1(--l);
            add2(l);
        }
        while(r > rr)
        {
            del1(r);
            del2(r--);
        }
        while(l < ll)
        {
            del1(l);
            del2(l++);
        }
        ans[q[i].id] = query1(q[i].b) - query1(q[i].a - 1);
        _ans[q[i].id] = query2(q[i].b) - query2(q[i].a - 1);
    }
    for(int i = 1; i <= m; i++)
    {
        write(ans[i]);
        putchar(' ');
        write(_ans[i]);
        putchar('\n');
    }
    return 0;
}
