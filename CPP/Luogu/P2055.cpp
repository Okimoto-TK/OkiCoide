#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>
#define N 300
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
} e[N * N];
int T;
int n, ptr, s, t;
bool og[N];
bool lv[N];
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
        ans += dfs(s, 0x3f3f3f3f);
    }
    return ans;
}
int main()
{
    for(scanf("%d", &T); T != 0; T--)
    {
        memset(head, -1, sizeof(head));
        memset(og, 0, sizeof(og));
        memset(lv, 0, sizeof(lv));
        ptr = 0;
        scanf("%d", &n);
        int cnt = 0;
        s = n * 2 + 1;
        t = s + 1;
        for(int i = 1; i <= n; i++)
        {
            int tmp;
            scanf("%d", &tmp);
            og[i] = tmp;
            if(og[i]) add_edge(i + n, t, 1);
            else add_edge(s, i, 1);
        }
        for(int i = 1; i <= n; i++)
        {
            int tmp;
            scanf("%d", &tmp);
            lv[i] = tmp;
            if(!lv[i] && og[i])
            {
                add_edge(s, i, 1);
                add_edge(i, i + n, 1);
            }
            if((og[i] && !lv[i]) || (!og[i])) cnt++;
        }
        for(int i = 1; i <= n; i++)
        {
            for(int j = 1; j <= n; j++)
            {
                int x;
                scanf("%d", &x);
                if(j >= i) continue;
                if(x == 0) continue;
                add_edge(i, j + n, 1);
                add_edge(j, i + n, 1);
            }
        }
        printf("%s\n", run() == cnt ? "^_^" : "T_T");
    }
    return 0;
}
