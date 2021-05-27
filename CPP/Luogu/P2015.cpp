#include <stdio.h>
#include <string.h>
using namespace std;
struct node
{
    int lc;
    int rc;
    int vl;
    int sz;
};
int n, q;
node t[107];
int f[107][107];
int vec[107][107];
int dfs(int u)
{
    t[u].sz = 1;
    for(int v = 1; v <= n; ++v)
    {
        if(vec[u][v] >= 0)
        {
            t[u].lc = v;
            t[v].vl = vec[u][v];
            vec[u][v] = -1;
            vec[v][u] = -1;
            t[u].sz += dfs(v);
            break;
        }
    }
    for(int v = 1; v <= n; ++v)
    {
        if(vec[u][v] >= 0)
        {
            t[u].rc = v;
            t[v].vl = vec[u][v];
            vec[u][v] = -1;
            vec[v][u] = -1;
            t[u].sz += dfs(v);
            break;
        }
    }
    return t[u].sz;
}
int getMax(int a, int b)
{
    return a > b ? a : b;
}
int dp(int u, int k)
{
    if(k == 0){ return 0; }
    int l = t[u].lc;
    int r = t[u].rc;
    int ans = t[u].vl;
    for(int i = 0; i <= k - 1; i++)
    {
        int x = i;
        int y = k - 1 - i;
        if(x <= t[l].sz && y <= t[r].sz){ ans = getMax((f[l][x] == -1 || f[r][y] == -1 ? dp(l, x) + dp(r, y) : f[l][x] + f[r][y]) + t[u].vl, ans); }
        else if(y > t[r].sz){ i += y - t[r].sz - 1; }
    }
    f[u][k] = ans;
    return ans;
}
int main()
{
    for(int i = 0; i < 107; i++){ for(int j = 0; j < 107; j++){ vec[i][j] = -1; f[i][j] = -1; }}
    scanf("%d%d", &n, &q);
    for(int i = 1; i < n; ++i)
    {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        vec[u][v] = w;
        vec[v][u] = w;
    }
    dfs(1);
    printf("%d", dp(1, q + 1));
    return 0;
}
