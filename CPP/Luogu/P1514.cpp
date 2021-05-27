#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
struct node
{
    int l;
    int r;
    node()
    {
        l = 1000;
        r = 0;
    }
};
int n, m;
int a[507][507];
bool vis[507][507];
node r[507];
void dfs(int rt, int x, int y)
{
    if(vis[x][y])
    {
        return;
    }
    if(x == 1)
    {
        r[rt].l = min(r[rt].l, y);
        r[rt].r = max(r[rt].r, y);
    }
    vis[x][y] = true;
    if(x - 1 >= 1 && a[x - 1][y] > a[x][y])
    {
        dfs(rt, x - 1, y);
    }
    if(x + 1 <= n && a[x + 1][y] > a[x][y])
    {
        dfs(rt, x + 1, y);
    }
    if(y - 1 >= 1 && a[x][y - 1] > a[x][y])
    {
        dfs(rt, x, y - 1);
    }
    if(y + 1 <= m && a[x][y + 1] > a[x][y])
    {
        dfs(rt, x, y + 1);
    }
}
bool cmp(node a, node b)
{
    if(a.l != b.l)
    {
        return a.l < b.l;
    }
    return a.r < b.r;
}
int main()
{
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= n; i++)
    {
        for(int j = 1; j <= m; j++)
        {
            scanf("%d", &a[i][j]);
        }
    }
    int cnt = 0;
    for(int i = 1; i <= m; i++)
    {
        memset(vis, 0, sizeof(vis));
        dfs(i, n, i);
        if(r[i].l == 1000)
        {
            cnt++;
        }
    }
    if(cnt)
    {
        printf("0\n%d", cnt);
        return 0;
    }
    sort(r + 1, r + 1 + n, cmp);
    int last = 0;
    int ans = 0;
    for(int i = 1; i <= m; i++)
    {
        if(last >= r[i].l && last <= r[i].r)
        {
            continue;
        }
        ans++;
        last = r[i].r;
    }
    printf("1\n%d", ans);
    return 0;
}
