#include <cstdio>
#include <cstring>
#include <queue>
int head[2][1005];
struct Edge
{
    int u, v, w, nxt;
    Edge()
    {
        u = v = w = nxt = -1;
    }
    Edge(int mode, int a, int b, int c)
    {
        u = a;
        v = b;
        w = c;
        nxt = head[mode][a];
    }
} e[2][100005];
struct Point
{
    int w, id;
    Point()
    {
        w = id = 0;
    }
    Point(int x, int y)
    {
        w = x;
        id = y;
    }
    bool operator< (const Point & p) const
    {
        return w > p.w;
    }
};
int n, m, x, ptr[2];
void addEdge(int mode, int a, int b, int c)
{
    e[mode][ptr[mode]] = Edge(mode, a, b, c);
    head[mode][a] = ptr[mode]++;
}
int dist[2][1005];
void Dijkstra(int s, int mode)
{
    bool vis[1005];
    std::priority_queue<Point> q;
    memset(dist[mode], 0x3f, sizeof(dist[mode]));
    memset(vis, 0, sizeof(vis));
    dist[mode][s] = 0;
    q.push(Point(0, x));
    while(!q.empty())
    {
        Point u = q.top();
        q.pop();
        if(vis[u.id]) continue;
        vis[u.id] = true;
        for(int i = head[mode][u.id]; i != -1; i = e[mode][i].nxt)
        {
            if(dist[mode][e[mode][i].v] > dist[mode][e[mode][i].u] + e[mode][i].w)
            {
                dist[mode][e[mode][i].v] = dist[mode][e[mode][i].u] + e[mode][i].w;
                q.push(Point(dist[mode][e[mode][i].v], e[mode][i].v));
            }
        }
    }
}
int main()
{
    memset(head, -1, sizeof(head));
    scanf("%d%d%d", &n, &m, &x);
    for(int i = 1; i <= m; i++)
    {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        addEdge(0, u, v, w);
        addEdge(1, v, u, w);
    }
    Dijkstra(x, 0);
    Dijkstra(x, 1);
    int ans = 0;
    for(int i = 1; i <= n; i++)
    {
        ans = std::max(ans, dist[0][i] + dist[1][i]);
    }
    printf("%d", ans);
    return 0;
}
