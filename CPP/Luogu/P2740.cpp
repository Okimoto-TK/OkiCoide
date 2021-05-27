#include <stdio.h>
#include <string.h>
#include <queue>
#include <algorithm>
using namespace std;
int head[1007];
int ver[1007];
int edge[1007];
int nxt[1007];
int d[1007];
int n, m, p = 1;
void add(int u, int v, int w)
{
    ver[++p] = v;
    edge[p] = w;
    nxt[p] = head[u];
    head[u] = p;
    ver[++p] = u;
    edge[p] = 0;
    nxt[p] = head[v];
    head[v] = p;
}
bool bfs()
{
    queue <int> q;
    memset(d, 0, sizeof(d));
    q.push(1);
    d[1] = 1;
    while(!q.empty())
    {
        int u = q.front();
        q.pop();
        for(int i = head[u]; i; i = nxt[i])
        {
            int v = ver[i];
            if(edge[i] && !d[v])
            {
                q.push(v);
                d[v] = d[u] + 1;
                if(v == m)
                {
                    return true;
                }
            }
        }
    }
    return false;
}
int dfs(int u, int w)
{
    if(u == m)
    {
        return w;
    }
    int r = w;
    for(int i = head[u]; i; i = nxt[i])
    {
        int v = ver[i];
        if(edge[i] && d[v] == d[u] + 1)
        {
            int l = dfs(v, min(r, edge[i]));
            if(!l)
            {
                d[v] = 0;
            }
            edge[i] -= l;
            edge[i ^ 1] += l;
            r -= l;
        }
    }
    return w - r;
}
int main()
{
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= n; i++)
    {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        add(u, v, w);
    }
    int f = 0;
    int ans = 0;
    while(bfs())
    {
        while(f = dfs(1, 0x3f3f3f3f))
        {
            ans += f;
        }
    }
    printf("%d", ans);
    return 0;
}
