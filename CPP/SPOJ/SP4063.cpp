#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>
#define N 200005
#define INF 0x7f7f7f7f
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
} e[N << 2];
int m, n, s, t, pool, ptr;
int addr[N];
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
				if(v == t) break;
				q.push(v);
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
int main()
{
	memset(head, -1, sizeof(head));
	scanf("%d%d", &m, &n);
	pool = m;
	s = ++pool;
	t = ++pool;
	for(int i = 1; i <= m; i++)
	{
		int x;
		scanf("%d", &x);
		add_edge(s, i, x);
		addr[i] = i;
	}
	for(int i = 1; i <= n; i++)
	{
		int v = ++pool;
		int x;
		scanf("%d", &x);
		for(int j = 1; j <= x; j++)
		{
			int u;
			scanf("%d", &u);
			add_edge(addr[u], v, INF);
			addr[u] = ++pool;
			add_edge(v, addr[u], INF);
		}
		int y;
		scanf("%d", &y);
		add_edge(v, t, y);
	}
	printf("%d", run());
	return 0;
}
