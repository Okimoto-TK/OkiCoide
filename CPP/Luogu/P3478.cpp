#include <stdio.h>
#include <vector>
#include <algorithm>
#define N 1000007
using namespace std;
int n;
vector<int> E[N];
int son[N];
pair<int, int> dfs1(int u, int f)
{
    int len = E[u].size();
    int res = 0;
    for(int i = 0; i < len; i++)
    {
        int v = E[u][i];
        if(v == f)
        {
            continue;
        }
        pair<int, int> buf = dfs1(v, u);
        res += buf.first + buf.second;
        son[u] += buf.second;
    }
    return make_pair(res, son[u] + 1);
}
long long buf;
long long lgs;
int ans = 1;
void dfs2(int u, int f)
{
    buf += n - 2 * son[u] - 1;
    if(buf > lgs)
    {
        ans = u;
        lgs = buf;
    }
    int len = E[u].size();
    for(int i = 0; i < len; i++)
    {
        int v = E[u][i];
        if(v == f)
        {
            continue;
        }
        dfs2(v, u);
    }
    buf -= n - 2 * son[u] - 1;
}
int main()
{
    scanf("%d", &n);
    for(int i = 1; i < n; i++)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        E[u].push_back(v);
        E[v].push_back(u);
    }
    lgs = buf = dfs1(1, 0).first;
    int len = E[1].size();
    for(int i = 0; i < len; i++)
    {
        int u = E[1][i];
        dfs2(u, 1);
    }
    printf("%d", ans);
    return 0;
}
