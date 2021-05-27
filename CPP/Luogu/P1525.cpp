#include <stdio.h>
#include <vector>
#include <string.h>
#include <algorithm>
using namespace std;
struct edge
{
    int v;
    int w;
    edge(int x, int y)
    {
        v = x;
        w = y;
    }
};
int n, m, ans, mx = 0, mn = 0x7f7f7f7f;
vector <edge> vec[100007];
int f[100007];
bool vis[100007];
bool can;
void dfs(int u, int t, int x)
{
    if(f[u] == 0){ f[u] = t; }
    else{ can = false; return; }
    for(int i = 0; i < vec[u].size(); i++)
    {
        int v = vec[u][i].v;
        if(!vis[v] && vec[u][i].w > x)
        {
            vis[v] = true;
            dfs(v, t * -1, x);
        }
        else if(vis[v] && vec[u][i].w > x)
        {
            if(f[v] != t * -1){ can = false; return; }
        }
    }
}
bool check(int x)
{
    memset(f, 0, sizeof(f));
    memset(vis, 0, sizeof(vis));
    can = true;
    for(int i = 1; i <= n; i++)
    {
        if(!vis[i])
        {
            vis[i] = true;
            dfs(i, 1, x);
        }
        if(!can)
        {
            return false;
        }
    }
    return true;
}
int main()
{
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= m; i++)
    {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        mx = max(mx, w);
        mn = min(mn, w);
        vec[u].push_back(edge(v, w));
        vec[v].push_back(edge(u, w));
    }
    int l = 0;
    int r = 1000000000;
    while(l <= r)
    {
        int mid = (l + r) / 2;
        if(check(mid))
        {
            ans = mid;
            r = mid - 1;
        }
        else
        {
            l = mid + 1;
        }
    }
    printf("%d", ans);
    return 0;
}
