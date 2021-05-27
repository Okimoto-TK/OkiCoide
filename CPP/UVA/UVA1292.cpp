#include <stdio.h>
#include <vector>
#include <string.h>
#include <algorithm>
#define N 2000
using namespace std;
int n;
vector<int> E[N];
int g[N][2];
int dfs(int u, int f, bool set)
{
    if(g[u][set ? 1 : 0] != 0)
    {
        return g[u][set ? 1 : 0];
    }
    int len = E[u].size();
    int res = set ? 1 : 0;
    for(int i = 0; i < len; i++)
    {
        int v = E[u][i];
        if(v == f)
        {
            continue;
        }
        if(set)
        {
            res += min(dfs(v, u, true), dfs(v, u, false));
        }
        else
        {
            res += dfs(v, u, true);
        }
    }
    g[u][set ? 1 : 0] = res;
    return res;
}
int main()
{
    while(scanf("%d", &n) != EOF)
    {
        for(int i = 1; i <= n; i++)
        {
            E[i].clear();
        }
        memset(g, 0, sizeof(g));
        for(int i = 1; i <= n; i++)
        {
            int u;
            scanf("%d:", &u);
            u++;
            int k;
            scanf("(%d)", &k);
            for(int j = 1; j <= k; j++)
            {
                int v;
                scanf("%d", &v);
                v++;
                E[u].push_back(v);
                E[v].push_back(u);
            }
        }
        printf("%d\n", min(dfs(1, 0, true), dfs(1, 0, false)));
    }
}
