#include <stdio.h>
#include <set>
#include <string.h>
using namespace std;
int n, m, ans;
set <int> map[1007];
bool vis[1007];
int lnk[1007];
bool dfs(int u)
{
    for(auto v : map[u])
    {
        if(!vis[v])
        {
            vis[v] = true;
            if(!lnk[v] || dfs(lnk[v]))
            {
                lnk[v] = u;
                return true;
            }
        }
    }
    return false;
}
int main()
{
    scanf("%d%d", &n, &m);
    for(int u = 1; u <= m; u++)
    {
        int s;
        scanf("%d", &s);
        for(int i = 1; i <= s; i++)
        {
            int v;
            scanf("%d", &v);
            map[u].insert(v);
        }
    }
    for(int i = 1; i <= m; i++)
    {
        memset(vis, 0, sizeof(vis));
        if(dfs(i)){ ans++; }
    }
    printf("%d", ans);
    return 0;
}
