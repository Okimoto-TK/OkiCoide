#include <stdio.h>
#include <set>
#include <string.h>
using namespace std;
int n, m, e, ans;
set <int> vec[10007];
bool vis[10007];
int lnk[10007];
bool dfs(int u)
{
    for(auto v : vec[u])
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
    scanf("%d", &n);
    for(int u = 1; u <= 2 * n; u++)
    {
        int v1, v2;
        scanf("%d%d", &v1, &v2);
        vec[u].insert(v1);
        vec[u].insert(v2);
        vec[u].insert(v1 + n);
        vec[u].insert(v2 + n);
    }
    for(int i = 1; i <= 2 * n; i++)
    {
        memset(vis, 0, sizeof(vis));
        if(dfs(i)){ ans++; }
    }
    printf("%d", ans);
    return 0;
}
