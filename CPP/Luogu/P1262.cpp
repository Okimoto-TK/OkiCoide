#include <stdio.h>
#include <vector>
#include <set>
#include <queue>
#include <algorithm>
using namespace std;
const int inf = 0x3f3f3f3f;
int n, m, d, t, p, r;
int prc[3007];
int lnk[3007];
int low[3007];
int dfn[3007];
int stk[3007];
int cst[3007];
int ind[3007];
bool vis[3007];
bool sel[3007];
vector <int> vec[3007];
set <int> map[3007];
void dfs(int u)
{
    dfn[u] = low[u] = ++d;
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
        cst[p] = inf;
        if(sel[u]){ cst[p] = prc[u]; }
        while(stk[t] != u)
        {
            lnk[stk[t]] = p;
            if(sel[stk[t]]){ cst[p] = min(cst[p], prc[stk[t]]); };
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
            if(lnk[v] != lnk[u])
            {
                map[lnk[u]].insert(lnk[v]);
            }
        }
    }
}
int topo()
{
    for(int u = 1; u <= p; u++)
    {
        for(auto v : map[u])
        {
            ind[v]++;
        }
    }
    int r = 0;
    for(int u = 1; u <= p; u++)
    {
        if(cst[u] == inf && ind[u] == 0){ return -1; }
        if(ind[u] == 0){ r += cst[u]; }
    }
    return r;
}
int flod()
{
    for(int s = 1; s <= p; s++)
    {
        if(cst[s] == inf){ continue; }
        queue <int> q;
        q.push(s);
        vis[s] = true;
        while(!q.empty())
        {
            int u = q.front();
            q.pop();
            for(auto v : map[u])
            {
                if(vis[v]){ continue; }
                vis[v] = true;
                q.push(v);
            }
        }
    }
    for(int i = 1; i <= n; i++)
    {
        if(vis[lnk[i]]){ continue; }
        return i;
    }
    return -1;
}
int main()
{
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= m; i++)
    {
        int id, pr;
        scanf("%d%d", &id, &pr);
        prc[id] = pr;
        sel[id] = true;
    }
    scanf("%d", &r);
    for(int i = 1; i <= r; i++)
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
    int r = topo();
    if(r == -1){ printf("NO\n%d", flod()); }
    else{ printf("YES\n%d", r); }
    return 0;
}
