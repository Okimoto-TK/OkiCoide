#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>
#define N 10000
#define INF 0x3f3f3f3f
int head[N];
struct edge
{
    int u, v, f, nxt;
    edge() { u = v = f = nxt = -1; }
    edge(int a, int b, int c)
    {
        u = a;
        v = b;
        f = c;
        nxt = head[a];
    }
} e[N * 100];
int p, c, n, s, t, ptr;
inline void add_edge(int a, int b, int c)
{
    e[ptr] = edge(a, b, c);
    head[a] = ptr++;
    e[ptr] = edge(b, a, 0);
    head[b] = ptr++;
}
int dep[N];
inline bool bfs()
{
    memset(dep, 0, sizeof(dep));
    dep[s] = 1;
    std::queue<int> q;
    q.push(s);
    while(!q.empty())
    {
        int u = q.front();
        q.pop();
        for(int i = head[u]; i != -1; i = e[i].nxt)
        {
            int v = e[i].v;
            if(dep[v] == 0 && e[i].f > 0)
            {
                dep[v] = dep[u] + 1;
                q.push(v);
                if(v == t) break;
            }
        }
    }
    return dep[t] != 0;
}
int cur[N];
int dfs(int u, int f)
{
    if(u == t) return f;
    int fsum = 0;
    for(int i = cur[u]; i != -1; i = e[i].nxt)
    {
        cur[u] = i;
        int v = e[i].v;
        if(dep[v] == dep[u] + 1 && e[i].f > 0)
        {
            int _f = dfs(v, std::min(f, e[i].f));
            e[i].f -= _f;
            e[i ^ 1].f += _f;
            f -= _f;
            fsum += _f;
            if(f <= 0) break;
        }
    }
    return fsum;
}
inline int run()
{
    int ans = 0;
    while(bfs())
    {
        memcpy(cur, head, sizeof(cur));
        ans += dfs(s, INF);
    }
    return ans;
}
bool ruin[N];
int main()
{
    memset(head, -1, sizeof(head));
    memset(ruin, 1, sizeof(ruin));
    scanf("%d%d%d", &p, &c, &n);
    s = 1 + p;
    t = 2 * p + 1;
    add_edge(s, 1, INF);
    for(int i = 1; i <= c; i++)
    {
        int a, b;
        scanf("%d%d", &a, &b);
        if(a == b) continue;
        add_edge(a + p, b, INF);
        add_edge(b + p, a, INF);
    }
    for(int i = 1; i <= n; i++)
    {
        int r;
        scanf("%d", &r);
        add_edge(r + p, t, INF);
        ruin[r] = false;
        add_edge(r, r + p, INF);
    }
    for(int i = 2; i <= p; i++)
    {
        if(ruin[i]) add_edge(i, i + p, 1);
    }
    printf("%d", run());
    return 0;
}
