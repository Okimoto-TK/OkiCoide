#include <stdio.h>
#include <string.h>
#include <math.h>
using namespace std;
struct circle
{
    int x;
    int y;
    int z;
};
int n, h, r, t;
bool con[1007][1007];
circle a[1007];
bool in[1007];
bool out[1007];
bool vis[1007];
bool dfs(int u)
{
    if(out[u])
    {
        return true;
    }
    bool ans = false;
    for(int i = 1; i <= n; i++)
    {
        if(con[u][i] && !vis[i])
        {
            vis[i] = true;
            ans |= dfs(i);
        }
    }
    return ans;
}
int main()
{
    scanf("%d", &t);
    for(int q = 1; q <= t; q++)
    {
        memset(con, 0, sizeof(con));
        memset(in, 0, sizeof(in));
        memset(out, 0, sizeof(out));
        memset(vis, 0, sizeof(vis));
        scanf("%d%d%d", &n, &h, &r);
        for(int i = 1; i <= n; i++)
        {
            scanf("%d%d%d", &a[i].x, &a[i].y, &a[i].z);
        }
        for(int i = 1; i <= n; i++)
        {
            if(r >= a[i].z)
            {
                in[i] = true;
            }
            if(r >= h - a[i].z)
            {
                out[i] = true;
            }
            for(int j = i + 1; j <= n; j++)
            {
                if(pow(a[i].x - a[j].x, 2) + pow(a[i].y - a[j].y, 2) + pow(a[i].z - a[j].z, 2) <= pow(2 * r, 2))
                {
                    con[i][j] = true;
                    con[j][i] = true;
                }
            }
        }
        bool ans = false;
        for(int i = 1; i <= n; i++)
        {
            if(in[i])
            {
                vis[i] = true;
                ans |= dfs(i);
            }
        }
        printf("%s\n", ans ? "Yes" : "No");
    }
    return 0;
}
