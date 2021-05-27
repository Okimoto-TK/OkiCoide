#include <stdio.h>
#include <vector>
using namespace std;
vector <int> vec[307];
int f[307][307];
int p[307];
int n, m;
int getMax(int a, int b){ return a > b ? a : b; }
void dfs(int u)
{
    for(int i = 0; i < vec[u].size(); ++i)
    {
        int v = vec[u][i];
        dfs(v);
    }
    for(int i = 0; i < vec[u].size(); i++)
    {
        int v = vec[u][i];
        for(int j = m; j >= 1; j--)
        {
            int _j = j - 1;
            for(int k = 0; k <= m; k++)
            {
                if(_j - k >= 0)
                {
                    f[u][_j] = getMax(f[u][_j], f[u][_j - k] + f[v][k]);
                }
            }
        }
    }
    for(int i = m; i >= 0; i --)
    {
        f[u][i + 1] = f[u][i] + p[u];
    }
    f[u][0] = 0;
}
int main()
{
    scanf("%d%d", &n, &m);
    m += 1;
    for(int i = 1; i <= n; ++i)
    {
        int k, s;
        scanf("%d%d", &k, &s);
        vec[k].push_back(i);
        p[i] = s;
    }
    dfs(0);
    printf("%d", f[0][m]);
    return 0;
}
