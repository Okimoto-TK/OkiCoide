#include <stdio.h>
#include <vector>
#include <set>
#include <queue>
#include <algorithm>
using namespace std;
int n, m, d, t, p;
int w[100007];
int stk[100007];
int lnk[100007];
int low[100007];
int dfn[100007];
int cnt[100007];
int cst[100007];
int ind[100007];
bool vis[100007];
set <int> map[100007];
vector <int> vec[100007];
void dfs(int u)
{
    low[u] = dfn[u] = ++d;
    stk[++t] = u;
    for(int i = 0; i < vec[u].size(); i++)
    {
        int v = vec[u][i];
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
        cst[p] = w[u];
        cnt[p] = 1;
        while(stk[t] != u)
        {
            if(w[stk[t]] < cst[p])
            {
                cst[p] = w[stk[t]];
                cnt[p] = 1;
            }
            else if(w[stk[t]] == cst[p])
            {
                cnt[p]++;
            }
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
            int v = vec[u][j];
            if(lnk[u] != lnk[v])
            {
                map[lnk[u]].insert(lnk[v]);
            }
        }
    }
}
void topo()
{
    for(int u = 1; u <= p; u++)
    {
        for(auto v : map[u])
        {
            ind[v]++;
        }
    }
    int ans = 0;
    int qua = 1;
    queue <int> q;
    for(int i = 1; i <= p; i++)
    {
        if(vis[i]){ continue; }
        q.push(i);
        vis[i] = true;
        ans += cst[i];
        qua *= cnt[i];
        while(!q.empty())
        {
            int u = q.front();
            q.pop();
            for(auto v : map[u])
            {
                if(vis[v]){ continue; }
                q.push(v);
                vis[v] = true;
            }
        }
    }
    printf("%d %d", ans, qua);
}
int main()
{
    scanf("%d", &n);
    for(int i = 1; i <= n; i++){ scanf("%d", &w[i]); }
    scanf("%d", &m);
    for(int i = 1; i <= m; i++)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        vec[u].push_back(v);
    }
    for(int i = 1; i <= n; i++)
    {
        if(!dfn[i]){ dfs(i); }
    }
    link();
    topo();
    return 0;
}
