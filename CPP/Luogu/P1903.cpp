#include <stdio.h>
#include <math.h>
#include <algorithm>
#define N 1919810
using namespace std;
int n, m, cntc, cntq, blocksize;
int a[N];
int cnt[N];
int ans[N];
struct query
{
    int l;
    int r;
    int c;
    int id;
    int bl;
    int br;
    query()
    {
    }
    query(int a1, int a2, int a3, int a4, int a5, int a6)
    {
        l = a1;
        r = a2;
        c = a3;
        id = a4;
        bl = a5;
        br = a6;
    }
} q[N];
struct change
{
    int x;
    int pre;
    int suf;
} c[N];
bool cmp(query a, query b)
{
    if(a.bl != b.bl)
    {
        return a.bl < b.bl;
    }
    if(a.br != b.br)
    {
        return a.br < b.br;
    }
    return a.c < b.c;
}
int main()
{
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= n; i++)
    {
        scanf("%d", &a[i]);
    }
    blocksize = 1620;
    for(int i = 1; i <= m; i++)
    {
        char opt[2];
        int x, y;
        scanf("%s%d%d", opt, &x, &y);
        if(opt[0] == 'R')
        {
            c[++cntc].pre = a[x];
            c[cntc].x = x;
            c[cntc].suf = y;
            a[x] = y;
        }
        else
        {
            ++cntq;
            q[cntq] = query(x, y, cntc, cntq, (x - 1) / blocksize + 1, (y - 1) / blocksize + 1);
        }
    }
    for(int i = cntc; i >= 1; i--)
    {
        a[c[i].x] = c[i].pre;
    }
    sort(q + 1, q + 1 + cntq, cmp);
    int t = 0;
    int l = 1;
    int r = 0;
    int tmp = 0;
    for(int i = 1; i <= cntq; i++)
    {
        int ll = q[i].l;
        int rr = q[i].r;
        int tt = q[i].c;
        while(l > ll)
        {
            tmp += !cnt[a[--l]]++;
        }
        while(l < ll)
        {
            tmp -= !--cnt[a[l++]];
        }
        while(r < rr)
        {
            tmp += !cnt[a[++r]]++;
        }
        while(r > rr)
        {
            tmp -= !--cnt[a[r--]];
        }
        while(t > tt)
        {
            int x = c[t].x;
            if(l <= x && x <= r)
            {
                tmp -= !--cnt[a[x]];
            }
            a[x] = c[t--].pre;
            if(l <= x && x <= r)
            {
                tmp += !cnt[a[x]]++;
            }
        }
        while(t < tt)
        {
            int x = c[++t].x;
            if(l <= x && x <= r)
            {
                tmp -= !--cnt[a[x]];
            }
            a[x] = c[t].suf;
            if(l <= x && x <= r)
            {
                tmp += !cnt[a[x]]++;
            }
        }
        ans[q[i].id] = tmp;
    }
    for(int i = 1; i <= cntq; i++)
    {
        printf("%d\n", ans[i]);
    }
    return 0;
}
