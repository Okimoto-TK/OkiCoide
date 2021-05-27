#include <stdio.h>
#include <math.h>
#include <algorithm>
#define MAX 100007
using namespace std;
int n, m, blocksize;
int a[MAX];
struct query
{
    int l;
    int r;
    int id;
    int bl;
} q[MAX];
bool cmp(query a, query b)
{
    if(a.bl != b.bl)
    {
        return a.bl < b.bl;
    }
    return (a.bl & 1) ? a.r < b.r : a.r > b.r;
}
int cnt[MAX];
int tmp;
void add(int x)
{
    if(cnt[a[x]]++ == a[x])
    {
        tmp--;
    }
    if(cnt[a[x]] == a[x])
    {
        tmp++;
    }
}
void del(int x)
{
    if(cnt[a[x]]-- == a[x])
    {
        tmp--;
    }
    if(cnt[a[x]] == a[x])
    {
        tmp++;
    }
}
int ans[MAX];
int main()
{
    scanf("%d%d", &n, &m);
    blocksize = sqrt(n) * 2;
    for(int i = 1; i <= n; i++)
    {
        scanf("%d", &a[i]);
        if(a[i] > n)
        {
            a[i] = n + 1;
        }
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
    for(int i = 1; i <= m; i++)
    {
        int ll = q[i].l;
        int rr = q[i].r;
        while(l > ll)
        {
            add(--l);
        }
        while(l < ll)
        {
            del(l++);
        }
        while(r < rr)
        {
            add(++r);
        }
        while(r > rr)
        {
            del(r--);
        }
        ans[q[i].id] = tmp;
    }
    for(int i = 1; i <= m; i++)
    {
        printf("%d\n", ans[i]);
    }
    return 0;
}
