#include <stdio.h>
#include <string.h>
#include <queue>
using namespace std;
int n, m, s, t, p = 1;
long long _max;
int ver[10007];
int nxt[10007];
int cap[10007];
int anc[10007];
int _min[10007];
int pre[10007];
bool vis[10007];
int getMin(int a, int b)
{
    return a < b ? a : b;
}
void add(int u, int v, int w)
{
    ver[++p] = v;
    cap[p] = w;
    nxt[p] = anc[u];
    anc[u] = p;
    ver[++p] = u;
    cap[p] = 0;
    nxt[p] = anc[v];
    anc[v] = p;
}
bool bfs()
{
    queue <int> q;
    q.push(s);
    memset(vis, 0, sizeof(vis));
    _min[s] = 1 << 29;
    vis[s] = true;
    while(!q.empty())
    {
        int x = q.front();
        q.pop();
        for(int i = anc[x]; i; i = nxt[i])
        {
            if(cap[i])
            {
                int y = ver[i];
                if(vis[y]){ continue; }
                _min[y] = getMin(_min[x], cap[i]);
                pre[y] = i;
                q.push(y);
                vis[y] = true;
                if(y == t)
                {
                    return true;
                }
            }
        }
    }
    return false;
}
void upd()
{
    int x = t;
    while(x != s)
    {
        int i = pre[x];
        cap[i ^ 1] += _min[t];
        cap[i] -= _min[t];
        x = ver[i ^ 1];
    }
    _max += _min[t];
}
int main()
{
    scanf("%d%d%d%d", &n, &m, &s, &t);
    for(int i = 1; i <= m; i++)
    {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        add(u, v, w);
    }
    while(bfs())
    {
        upd();
    }
    printf("%lld", _max);
    return 0;
}
