#include <stdio.h>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;
int n, m, d, t, p;
int dfn[100007];
int stk[100007];
int low[100007];
int lnk[100007];
int ind[100007];
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
        while(stk[t] != u)
        {
            lnk[stk[t]] = p;
            t--;
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
    int ans = 0;
    for(int u = 1; u <= p; u++)
    {
        for(auto v : map[u])
        {
            ind[v]++;
        }
    }
    for(int i = 1; i <= p; i++)
    {
        if(ind[i] == 0){ ans++; }
    }
    printf("%d", ans);
}
int main()
{
    scanf("%d%d", &n, &m);
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
