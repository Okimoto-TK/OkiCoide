#include <stdio.h>
#include <vector>
#include <algorithm>
using namespace std;
int n;
int a[16007];
int f[16007];
vector <int> vec[16007];
int dfs(int s, int u)
{
    int mx = 0;
    int len = vec[u].size();
    for(int i = 0; i < len; i++)
    {
        int v = vec[u][i];
        if(s == v)
        {
            continue;
        }
        mx += max(0, dfs(u, v));
    }
    f[u] = mx + a[u];
    return f[u];
}
int main()
{
    scanf("%d", &n);
    for(int i = 1; i <= n; i++)
    {
        scanf("%d", &a[i]);
    }
    for(int i = 1; i < n; i++)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        vec[u].push_back(v);
        vec[v].push_back(u);
    }
    dfs(0, 1);
    int ans = -200000000;
    for(int i = 1; i <= n; i++)
    {
        ans = max(ans, f[i]);
    }
    printf("%d", ans);
    return 0;
}
