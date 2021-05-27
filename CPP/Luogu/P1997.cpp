#include <stdio.h>
#include <math.h>
#include <algorithm>
#define N 500007
using namespace std;
int n, m, blocksize;
int a[N];
struct query
{
    int l;
    int r;
    int id;
    int bl;
} q[2 * N];
bool cmp(query a, query b)
{
    if(a.bl != b.bl)
    {
        return a.bl < b.bl;
    }
    return a.r < b.r;
}
int res, tmp;
int val[2 * N];
int cnt[2 * N];
int ans[2 * N];
void add(int x)
{
    --val[cnt[a[x]]];
    ++val[++cnt[a[x]]];
    if(cnt[a[x]] > res)
    {
        res = cnt[a[x]];
    }
}
void del(int x)
{
    --val[cnt[a[x]]];
    ++val[--cnt[a[x]]];
    if(val[res] == 0)
    {
        if(cnt[a[x]] == res - 1)
        {
            res--;
        }
    }
}
int main()
{
    scanf("%d%d", &n, &m);
    blocksize = 2 * sqrt(n);
    for(int i = 1; i <= n; i++)
    {
        scanf("%d", &a[i]);
    }
    for(int i = 1; i <= m; i++)
    {
        scanf("%d%d", &q[i].l, &q[i].r);
        q[i].id = i;
        q[i].bl = (q[i].l - 1) / blocksize + 1;
    }
    sort(q + 1, q + 1 + m, cmp);
    int l = 1;
    int r = 0;
    val[0] = n;
    for(int i = 1; i <= m; i++)
    {
        int ll = q[i].l;
        int rr = q[i].r;
        while(l > ll)
        {
            add(--l);
        }
        while(r < rr)
        {
            add(++r);
        }
        while(l < ll)
        {
            del(l++);
        }
        while(r > rr)
        {
            del(r--);
        }
        ans[q[i].id] = res;
    }
    for(int i = 1; i <= m; i++)
    {
        printf("%d\n", ans[i]);
    }
    return 0;
}
