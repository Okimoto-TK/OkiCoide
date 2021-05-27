#include <stdio.h>
#include <string.h>
#include <vector>
#include <queue>
#include <set>
#include <algorithm>
using namespace std;
int n, c, p, t, ans;
int stk[107];
int dfs[107];
int lnk[107];
int low[107];
int idg[107];
int odg[107];
int siz[107];
int vis[107];
vector <int> vec[107];
set <int> map[107];
queue <int> q;
void tarjan(int u)
{
    stk[++t] = u;
    dfs[u] = low[u] = ++c;
    for(int i = 0; i < vec[u].size(); i++)
    {
        int v = vec[u][i];
        if(!dfs[v])
        {
            tarjan(v);
            low[u] = min(low[u], low[v]);
        }
        else if(!lnk[v]){ low[u] = min(low[u], dfs[v]); }
    }
    if(low[u] == dfs[u])
    {
        lnk[u] = ++p;
        siz[p] = 1;
        while(stk[t] != u)
        {
            lnk[stk[t--]] = p;
            siz[p]++;
        }
        t--;
    }
}
void link()
{
    for(int u = 1; u <= n; u++)
    {
        for(int i = 0; i < vec[u].size(); i++){
            int v = vec[u][i];
            if(lnk[u] != lnk[v])
            {
                map[lnk[u]].insert(lnk[v]);
            }
        }
    }
}
void topo(){
    for(int u = 1; u <= p; u++)
    {
        for(auto v : map[u])
        {
            odg[u]++;
            idg[v]++;
        }
    }
}

int main()
{
    scanf("%d", &n);
    for(int u = 1; u <= n; u++)
    {
        int v;
        scanf("%d", &v);
        while(v != 0)
        {
            vec[u].push_back(v);
            scanf("%d", &v);
        }
    }
    for(int s = 1; s <= n; s++)
    {
        if(!dfs[s]){ tarjan(s); }
    }
    link();
    topo();
    int inc = 0;
    int otc = 0;
    for(int i = 1; i <= p; i++)
    {
        if(idg[i] == 0){ inc++; }
        if(odg[i] == 0){ otc++; }
    }
    if(p == 1)
    {
        printf("1\n0");
        return 0;
    }
    printf("%d\n%d", inc, max(inc, otc));
}
