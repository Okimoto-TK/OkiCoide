#include <stdio.h>
#include <algorithm>
#include <vector>
using namespace std;
int n, r, m;
vector <int> f[10007];
vector <int> g[10007];
int ans[10007];
int siz[10007];
int dfs(int s, int u)
{
    ans[u] = 1;
    siz[u] = 1;
    int len = f[u].size();
    for(int i = 0; i < len; i++)
    {
        int v = f[u][i];
        if(s == v)
        {
            continue;
        }
        g[u].push_back(v);
        int buf = dfs(u, v);
        (ans[u] += buf * siz[u] % 1000000007) %= 1000000007;
        siz[u] += buf;
    }
    return siz[u];
}
int main()
{
    scanf("%d%d%d", &n, &r, &m);
    for(int i = 1; i < n; i++)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        f[u].push_back(v);
        f[v].push_back(u);
    }
    dfs(0, r);
    for(int i = 1; i <= m; i++)
    {
        int p;
        scanf("%d", &p);
        printf("%d\n", ans[p] * 2 - 1);
    }
}
