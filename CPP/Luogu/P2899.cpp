#include <stdio.h>
#include <vector>
#include <algorithm>
#define N 200007
using namespace std;
int n;
vector<int> g[N];
int ans;
int dfs(int u, int spr)
{
    int len = g[u].size();
    int res = -1;
    for(int i = 0; i < len; i++)
    {
        int v = g[u][i];
        if(v == spr)
        {
            continue;
        }
        int r = dfs(v, u);
        if(r == -1)
        {
            res = 1;
        }
        else if(r == 1 && res == -1)
        {
            res = 0;
        }
    }
    ans += (res == 1);
    return res;
}
int main()
{
    scanf("%d", &n);
    for(int i = 1; i < n; i++)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        g[u].push_back(v);
        g[v].push_back(u);
    }
    if(dfs(1, 0) == -1)
    {
        ans++;
    }
    printf("%d", ans);
    return 0;
}
