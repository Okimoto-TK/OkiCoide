#include <stdio.h>
#include <string.h>
#include <queue>
#include <vector>
using namespace std;
struct edge
{
    int u, v, w;
    edge(const int &_u, const int &_v, const int &_w)
    {
        u = _u;
        v = _v;
        w = _w;
    }
};
int n, m;
int ans[5007];
int cnt[5007];
bool vis[5007];
vector <edge> e[5007];
void add(int u, int v, int w)
{
    e[u].push_back(edge(u, v, w));
}
bool bfd()
{
    memset(cnt, 0, sizeof(cnt));
    memset(ans, 0x3f, sizeof(ans));
    memset(vis, 0, sizeof(vis));
    queue <int> q;
    ans[0] = 0;
    vis[0] = true;
    q.push(0);
    while(!q.empty())
    {
        int u = q.front();
        cnt[u]++;
        q.pop();
        if(cnt[u] > n - 1){ return false; }
        vis[u] = false;
        for(int i = 0; i < e[u].size(); i++)
        {
            edge x = e[u][i];
            int v = x.v;
            int w = x.w;
            if(ans[v] > ans[u] + w)
            {
                ans[v] = ans[u] + w;
                if(!vis[v])
                {
                    q.push(v);
                    vis[v] = true;
                }
            }
        }
    }
    return true;
}
int main()
{
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= n; i++){ add(0, i, 0); }
    for(int i = 1; i <= m; i++)
    {
        int v, u, w;
        scanf("%d%d%d", &v, &u, &w);
        add(u, v, w);
    }
    if(!bfd()){ printf("NO"); }
    else
    {
        for(int i = 1; i <= n; i++){ printf("%d ", ans[i]); }
    }
    return 0;
}
