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
} e[400005];
int n, m, s, t, ptr;
int dx[] = {0, 1, 1, -1, -1, 2, 2, -2, -2};
int dy[] = {0, 2, -2, 2, -2, 1, -1, 1, -1};
bool a[205][205];
inline bool check(int x, int y)
{
    return !a[x][y] && x >= 1 && x <= n && y >= 1 && y <= n;
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
    return (x - 1) * n + y;
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
    memset(head, -1, sizeof(head));
    scanf("%d", &n);
    s = n * n + 1;
    t = s + 1;
    for(int i = 1; i <= n; i++)
	{
		for(int j = 1; j <= n; j++)
		{
			int x;
			scanf("%1d", &x);
			a[i][j] = x == 1;
			m += x;
		}
	}
    for(int i = 1; i <= n; i++)
    {
        for(int j = 1; j <= n; j++)
        {
            if(check(i, j))
            {
                if(((i + j) & 1) == 0) add_edge(get(i, j), t, 1);
                else add_edge(s, get(i, j), 1);
            }
            if(((i + j) & 1) != 0)
            {
                for(int k = 1; k <= 8; k++)
                {
                    if(check(i + dx[k], j + dy[k])) add_edge(get(i, j), get(i + dx[k], j + dy[k]), 1);
                }
            }
        }
    }
    printf("%d", n * n - m - run());
    return 0;
}

