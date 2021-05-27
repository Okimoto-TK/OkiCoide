#include <stdio.h>
#include <vector>
using namespace std;
int n;
int ans;
int g_min = 0x7f7f7f7f;
vector <int> vec[50007];
vector <int> chd[50007];
int spr[50007];
int son[50007];
int f[50007];
int dfs1(int u, int sup)
{
    son[u] = 0;
    for(int i = 0; i < vec[u].size(); i++)
    {
        int v = vec[u][i];
        if(v == sup){ continue; }
        chd[u].push_back(v);
        spr[v] = u;
        son[u] += dfs1(v, u) + 1;
    }
    return son[u];
}
void dfs2(int u)
{
    f[1] += son[u];
    for(int i = 0; i < chd[u].size(); i++)
    {
        int v = chd[u][i];
        dfs2(v);
    }
}
void dp(int u)
{
    f[u] = f[spr[u]];
    f[u] += (n - 1 - son[u]);
    f[u] -= son[u] + 1;
    for(int i = 0; i < chd[u].size(); i++)
    {
        int v = chd[u][i];
        dp(v);
    }
}
int main()
{
    scanf("%d", &n);
    for(int i = 1; i < n; ++i)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        vec[u].push_back(v);
        vec[v].push_back(u);
    }
    dfs1(1, 0);
    dfs2(1);
    for(int i = 0; i < chd[1].size(); i++)
    {
        dp(chd[1][i]);
    }
    for(int i = 1; i <= n; ++i)
    {
        if(f[i] < g_min){
            ans = i;
            g_min = f[i];
        }
    }
    printf("%d %d", ans, g_min);
    return 0;
}
