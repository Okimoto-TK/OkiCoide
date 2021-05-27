#include <stdio.h>
#include <string.h>
#include <set>
#include <vector>
#include <algorithm>
using namespace std;
struct edge
{
    int fr;
    int to;
};
int n, m, d, t, p, b;
bool lnk[1007];
int stk[1007];
int dfn[1007];
int low[1007];
bool cut[1007];
vector <int> vec[1007];
vector <int> blk[1007];
void dfs(int u, int s)
{
    int c = 0;
    low[u] = dfn[u] = ++d;
    stk[++t] = u;
    int l = vec[u].size();
    for(int i = 0; i < l; i++)
    {
        int v = vec[u][i];
        if(!dfn[v])
        {
            c++;
            dfs(v, s);
            low[u] = min(low[u], low[v]);
            if((u == s && c > 1) || (u != s && dfn[u] <= low[v]))
            {
                cut[u] = true;
            }
            if(dfn[u] <= low[v])
            {
                blk[++b].clear();
                do
                {
                    blk[b].push_back(stk[t--]);
                }while(stk[t + 1] != v);
                blk[b].push_back(u);
            }
        }
        else{ low[u] = min(low[u], dfn[v]); }
    }
}
int main()
{
    int i = 1;
    for(scanf("%d", &m); m != 0; scanf("%d", &m))
    {
        memset(lnk, 0, sizeof(lnk));
        memset(stk, 0, sizeof(stk));
        memset(dfn, 0, sizeof(dfn));
        memset(low, 0, sizeof(low));
        memset(cut, 0, sizeof(cut));
        for(int j = 0; j < 1007; j++){ vec[j].clear(); }
        d = t = p = b = n = 0;
        printf("Case %d: ", i);
        for(int j = 1; j <= m; j++)
        {
            int u, v;
            scanf("%d%d", &u, &v);
            vec[u].push_back(v);
            vec[v].push_back(u);
            n = max(n, max(u, v));
        }
        for(int i = 1; i <= n; i++)
        {
            if(!dfn[i]){ dfs(i, i); }
        }
        int r = 0;
        long long c = 1;
        for(int j = 1; j <= b; j++)
        {
            int l = blk[j].size();
            int g = 0;
            for(int k = 0; k < l; k++)
            {
                int o = blk[j][k];
                if(cut[o]){ g++; }
            }
            if(g == 0)
            {
                r += 2;
                c = c * (l - 1) * l / 2;
            }
            else if(g == 1)
            {
                r += 1;
                c = c * (l - 1);
            }
        }
        printf("%d %lld\n", r, c);
        i++;
    }
    return 0;
}
