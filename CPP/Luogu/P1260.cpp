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
int t, n, m;
int ans[10007];
int cnt[10007];
bool vis[10007];
vector <edge> e[10007];
void add(int u, int v, int w)
{
    e[u].push_back(edge(u, v, w));
}
bool bfd()
{
    memset(cnt, 0, sizeof(cnt));
    memset(ans, 63, sizeof(ans));
    memset(vis, 0, sizeof(vis));
    queue <int> q;
    ans[1] = 0;
    vis[1] = true;
    q.push(1);
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
    freopen("in.in", "r", stdin);
    freopen("out.out", "w", stdout);
    scanf("%d", &t);
    while(t)
    {
        printf("%d\n", t);
        scanf("%d%d", &n, &m);
        for(int i = 1; i <= m; i++)
        {
            int u, v, w;
            scanf("%d%d%d", &u, &v, &w);
            if(w >= 0){
                add(u, v, w);
                add(v, u, w);
            }
            else{ add(u, v, w); }
        }
        if(!bfd()){ printf("YES\n"); }
        else{ printf("NO\n"); }
        t--;
    }
    return 0;
}
