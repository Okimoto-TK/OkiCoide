#include <stdio.h>
#include <string.h>
#include <vector>
#include <set>
#include <queue>
#include <algorithm>
using namespace std;
int n, m, p, top, rec, ans;
int to[10007];
int dfs[10007];
int low[10007];
int stk[10007];
int siz[10007];
bool cn[10007];
bool bn[10007];
vector <int> vec[10007];
set <int> map[10007];
void tarjan(int u)
{
    dfs[u] = low[u] = ++rec;
    stk[++top] = u;
    for(int i = 0; i < vec[u].size(); i++)
    {
        int v = vec[u][i];
        if(!dfs[v])
        {
            tarjan(v);
            low[u] = min(low[u], low[v]);
        }
        else if(!to[v]){ low[u] = min(low[u], dfs[v]); }
    }
    if(dfs[u] == low[u])
    {
        to[u] = ++p;
        siz[p] = 1;
        while(stk[top] != u)
        {
            to[stk[top--]] = p;
            siz[p]++;
        }
        --top;
    }
}
void link()
{
    for(int u = 0; u <= n; u++)
    {
        for(int i = 0; i < vec[u].size(); i++)
        {
            int v = vec[u][i];
            if(to[u] == to[v]){ continue; }
            map[to[v]].insert(to[u]);
            cn[to[u]] = true;
        }
    }
}
void topo(int s)
{
    if(cn[s]){ return; }
    memset(bn, 0, sizeof(bn));
    queue <int> q;
    q.push(s);
    bn[s] = true;
    while(!q.empty())
    {
        int u = q.front();
        q.pop();
        for(auto v : map[u])
        {
            if(!bn[v])
            {
                bn[v] = true;
                q.push(v);
            }
        }
    }
    bool flag = true;
    for(int i = 1; i <= p; i++)
    {
        if(!bn[i])
        {
            flag = false;
            break;
        }
    }
    if(flag){ ans += siz[s]; }
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
    for(int i = 1; i <= n; i++){ vec[0].push_back(i); }
    tarjan(0);
    link();
    for(int i = 1; i <= p; i++){ topo(i); }
    printf("%d", ans);
    return 0;
}
