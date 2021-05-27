#include <stdio.h>
#include <algorithm>
#include <vector>
#define N 2000
using namespace std;
int n;
int ans;
int vl[N];
int f[N][3];
vector<int> E[N];
void dfs(int u, int fa)
{
    f[u][0] = vl[u];
    int len = E[u].size();
    bool slc = false;
    int reg = 0x3f3f3f3f;
    for(int i = 0; i < len; i++)
    {
        int v = E[u][i];
        if(v == fa)
        {
            continue;
        }
        dfs(v, u);
        int tmp = min(f[v][0], f[v][1]);
        f[u][0] += min(f[v][2], tmp);
        f[u][2] += tmp;
        if(f[v][0] < f[v][1])
        {
            slc = true;
        }
        else
        {
            reg = min(reg, f[v][0] - f[v][1]);
        }
        f[u][1] += tmp;
    }
    if(!slc)
    {
        f[u][1] += reg;
    }
}
int main()
{
    scanf("%d", &n);
    for(int i = 1; i <= n; i++)
    {
        int u, k, m;
        scanf("%d%d%d", &u, &k, &m);
        vl[u] = k;
        for(int j = 1; j <= m; j++)
        {
            int v;
            scanf("%d", &v);
            E[u].push_back(v);
            E[v].push_back(u);
        }
    }
    dfs(1, 0);
    printf("%d", min(f[1][0], f[1][1]));
    return 0;
}
