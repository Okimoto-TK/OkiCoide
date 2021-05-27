#include <stdio.h>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;
int n, m, d, t, p;
int a[1007];
int b[1007];
int w[1007];
int vl[1007];
int f[1007][1007];
int _f[1007][1007];
int lnk[1007];
int stk[1007];
int low[1007];
int dfn[1007];
int ind[1007];
int req[1007];
vector <int> vec[1007];
set <int> map[1007];
void dfs(int u)
{
    low[u] = dfn[u] = ++d;
    stk[++t] = u;
    int len = vec[u].size();
    for(int i = 0; i < len; i++)
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
            lnk[stk[t--]] = p;
        }
        t--;
    }
}
void link()
{
    for(int u = 1; u <= n; u++)
    {
        w[lnk[u]] += a[u];
        vl[lnk[u]] += b[u];
        if(lnk[req[u]] != lnk[u])
        {
            map[lnk[req[u]]].insert(lnk[u]);
            ind[lnk[u]]++;
        }
    }
}
void dp(int u)
{
    for(int i = w[u]; i <= m; i++){ f[u][i] = vl[u]; }
    for(auto v : map[u])
    {
        dp(v);
        for(int i = m - w[u]; i >= 0; i--)
        {
            for(int k = 0; k <= i; k++)
            {
                f[u][i + w[u]] = max(f[u][i + w[u]], f[u][i + w[u] - k] + f[v][k]);
            }
        }
    }
}
void topo()
{
    for(int i = 1; i <= p; i++)
    {
        if(ind[i] == 0)
        {
            map[0].insert(i);
        }
    }
    dp(0);
    printf("%d", f[0][m]);
}
int main()
{
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= n; i++)
    {
        scanf("%d", &a[i]);
    }
    for(int i = 1; i <= n; i++)
    {
        scanf("%d", &b[i]);
    }
    for(int u = 1; u <= n; u++)
    {
        int v;
        scanf("%d", &v);
        req[u] = v;
        if(v){ vec[v].push_back(u); }
    }
    for(int i = 1; i <= n; i++)
    {
        if(!dfn[i]){ dfs(i); }
    }
    link();
    topo();
    return 0;
}
