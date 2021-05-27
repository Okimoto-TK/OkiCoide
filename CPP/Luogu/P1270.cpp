#include <stdio.h>
#include <algorithm>
#define N 1000
using namespace std;
struct node
{
    int lc;
    int rc;
    int c;
    int p;
} a[N];
int s, pool;
int dfs1()
{
    int u = ++pool;
    scanf("%d%d", &a[u].c, &a[u].p);
    a[u].c *= 2;
    if(a[u].p == 0)
    {
        a[u].lc = dfs1();
        a[u].rc = dfs1();
    }
    return u;
}
int f[N][607];
int dfs2(int u, int vl)
{
    vl -= a[u].c;
    if(f[u][vl] > 0)
    {
        return f[u][vl];
    }
    if(a[u].p)
    {
        return vl >= 0 ? min(a[u].p, vl / 5) : 0;
    }
    if(vl <= 0)
    {
        return 0;
    }
    int res = 0;
    for(int i = 0; i <= vl; i++)
    {
        res = max(res, dfs2(a[u].lc, i) + dfs2(a[u].rc, vl - i));
    }
    f[u][vl] = res;
    return res;
}
int main()
{
    scanf("%d", &s);
    s--;
    dfs1();
    printf("%d", dfs2(1, s));
    return 0;
}
