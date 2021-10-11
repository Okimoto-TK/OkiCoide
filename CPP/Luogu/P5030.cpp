#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>
int head[40005];
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
} e[800005];
int n, m, k, s, t, ptr;
int dx[] = {0, 1, 1, -1, -1, 3, 3, -3, -3};
int dy[] = {0, 3, -3, 3, -3, 1, -1, 1, -1};
bool a[205][205];
inline bool check(int x, int y)
{
    return !a[x][y] && x >= 1 && x <= n && y >= 1 && y <= m;
}
inline void add_edge(int a, int b, int c)
{
    e[ptr] = edge(a, b, c);
    head[a] = ptr++;
    e[ptr] = edge(b, a, 0);
    head[b] = ptr++;
}
inline int get(int x, int y)
{
    return (x - 1) * m + y;
}
int dep[40005];
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
int cur[40005];
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
        ans += dfs(s, 0x3f3f3f3f);
    }
    return ans;
}
int main()
{
    int cnt = 0;
    memset(head, -1, sizeof(head));
    scanf("%d%d%d", &n, &m, &k);
    s = n * m + 1;
    t = s + 1;
    for(int i = 1; i <= k; i++)
    {
        int x, y;
        scanf("%d%d", &x, &y);
        if(!a[x][y]) cnt++;
        a[x][y] = true;
    }
    for(int i = 1; i <= n; i++)
    {
        for(int j = 1; j <= m; j++)
        {
            if(check(i, j))
            {
                if((i & 1) == 0) add_edge(get(i, j), t, 1);
                else add_edge(s, get(i, j), 1);
            }
            if((i & 1) != 0)
            {
                for(int u = 1; u <= 8; u++)
                {
                    if(check(i + dx[u], j + dy[u])) add_edge(get(i, j), get(i + dx[u], j + dy[u]), 1);
                }
            }
        }
    }
    printf("%d", n * m - cnt - run());
    return 0;
}
