#include <stdio.h>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
int n, m, p, top, rec;
int to[20007];
int dfs[20007];
int low[20007];
int stk[20007];
bool ans[20007];
int num;
vector <int> vec[20007];
void tarjan(int u, int s)
{
    int cnt = 0;
    dfs[u] = low[u] = ++rec;
    stk[++top] = u;
    for(int i = 0; i < vec[u].size(); i++)
    {
        int v = vec[u][i];
        if(!dfs[v])
        {
            tarjan(v, s);
            cnt++;
            if(u != s && dfs[u] <= low[v])
            {
                if(!ans[u]){ num++; }
                ans[u] = true;
            }
            low[u] = min(low[u], low[v]);
        }
        else if(!to[v]){ low[u] = min(low[u], dfs[v]); }
    }
    if(dfs[u] == low[u])
    {
        to[u] = ++p;
        while(stk[top] != u)
        {
            to[stk[top--]] = p;
        }
        --top;
    }
    if(u == s && cnt > 1)
    {
        ans[u] = true;
        num++;
    }
}
int main()
{
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= m; i++)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        vec[u].push_back(v);
        vec[v].push_back(u);
    }
    for(int i = 1; i <= n; i++)
    {
        if(!dfs[i]){ tarjan(i, i); }
    }
    printf("%d\n", num);
    for(int i = 1; i <= n; i++)
    {
        if(ans[i]){ printf("%d ", i); }
    }
    return 0;
}
