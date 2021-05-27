#include <stdio.h>
#include <vector>
#include <set>
#include <queue>
using namespace std;
int n, m, p, c;
int a[1000007];
int dfs[1000007];
int low[1000007];
int stk[1000007];
int lnk[1000007];
int cnt[1000007];
int ans[1000007];
int sum[1000007];
int top;
vector <int> vec[1000007];
set <int> map[1000007];
queue <int> q;
int min(int a, int b){ return a < b ? a : b; }
int max(int a, int b){ return a > b ? a : b; }
void tarj(int u)
{
    dfs[u] = ++c;
    low[u] = dfs[u];
    stk[++top] = u;
    for(int i = 0; i < vec[u].size(); ++i)
    {
        int v = vec[u][i];
        if(!dfs[v])
        {
            tarj(v);
            low[u] = min(low[u], low[v]);
        }
        else if(!lnk[v]){ low[u] = min(low[u], dfs[v]); }
    }
    if(low[u] == dfs[u])
    {
        lnk[u] = ++p;
        while(stk[top] != u){ lnk[stk[top--]] = p; }
        top--;
    }
}
void link()
{
    for(int i = 0; i <= n; i++)
    {
        for(int j = 0; j < vec[i].size(); ++j)
        {
            int u = i;
            int v = vec[u][j];
            if(lnk[u] == lnk[v]){ continue; }
            map[lnk[u]].insert(lnk[v]);
        }
        sum[lnk[i]] += a[i];
    }
}
void topo()
{
    for(int i = 1; i <= p; i++)
    {
        int u = i;
        for(auto j : map[u])
        {
            cnt[j] ++;
        }
    }
    for(int i = 1; i <= p; i++)
    {
        if(cnt[i] == 0){ q.push(i); ans[i] = sum[i];}
    }
}
int main()
{
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= n; ++i){ scanf("%d", &a[i]); }
    for(int i = 1; i <= m; ++i)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        vec[u].push_back(v);
    }
    for(int i = 1; i <= n; ++i){ vec[0].push_back(i); }
    tarj(0);
    link();
    topo();
    while(!q.empty())
    {
        int u = q.front();
        q.pop();
        for(auto i : map[u])
        {
            int v = i;
            ans[v] = max(ans[v], ans[u] + sum[v]);
            if(--cnt[v] == 0){ q.push(v); }
        }
    }
    int res = 0;
    for(int i = 1; i <= p; i++){ res = max(res, ans[i]); }
    printf("%d", res);
    return 0;
}
