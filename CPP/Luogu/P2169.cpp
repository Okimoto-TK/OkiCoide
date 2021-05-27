#include <stdio.h>
#include <string.h>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
struct edge
{
    int v;
    int w;
};
struct node
{
    int i;
    int w;
    bool operator<(const node &x) const
    {
        return w < x.w;
    }
};
int n, m, d, t, p;
int lnk[200007];
int low[200007];
int dfn[200007];
int stk[200007];
int ans[200007];
bool vis[200007];
vector <edge> vec[200007];
vector <edge> map[200007];
priority_queue <node> q;
void dfs(int u)
{
    low[u] = dfn[u] = ++d;
    stk[++t] = u;
    for(int i = 0; i < vec[u].size(); i++)
    {
        edge e = vec[u][i];
        int v = e.v;
        int w = e.w;
        if(!dfn[v])
        {
            dfs(v);
            low[u] = min(low[u], low[v]);
        }
        else if(!lnk[v])
        {
            low[u] = min(low[u], dfn[v]);
        }
    }
    if(low[u] == dfn[u])
    {
        lnk[u] = ++p;
        while(stk[t] != u)
        {
            lnk[stk[t--]] = p;
        }
        t--;
    }
}
void link()
{
    for(int u = 1; u <= n; u++)
    {
        for(int j = 0; j < vec[u].size(); j++)
        {
            edge e = vec[u][j];
            int v = e.v;
            int w = e.w;
            if(lnk[u] != lnk[v])
            {
                e.v = lnk[v];
                map[lnk[u]].push_back(e);
            }
        }
    }
}
void dij(int s)
{
    memset(ans, 0x3f, sizeof(ans));
    memset(vis, 0, sizeof(vis));
    ans[s] = 0;
    q.push(node{s, 0});
    while(!q.empty())
    {
        node e = q.top();
        q.pop();
        int u = e.i;
        if(vis[u]){ continue; }
        vis[u] = true;
        for(int i = 0; i < map[u].size(); i++)
        {
            edge e = map[u][i];
            int v = e.v;
            int w = e.w;
            if(ans[v] > ans[u] + w)
            {
                ans[v] = ans[u] + w;
                q.push(node{v, ans[v]});
            }
        }
    }
}
int main()
{
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= m; i++)
    {
        edge e;
        int u;
        scanf("%d%d%d", &u, &e.v, &e.w);
        vec[u].push_back(e);
    }
    for(int i = 1; i <= n; i++)
    {
        if(!dfn[i]){ dfs(i); }
    }
    link();
    dij(lnk[1]);
    printf("%d", ans[lnk[n]]);
    return 0;
}
