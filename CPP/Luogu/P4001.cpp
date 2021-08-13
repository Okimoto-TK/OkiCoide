#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>
int head[1000005];
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
} e[6000005];
int n, m, s, t, ptr;
inline int get(int x, int y)
{
	return (x - 1) * m + y;
}
inline void add_edge(int a, int b, int c, int _c)
{
	e[ptr] = edge(a, b, c);
	head[a] = ptr++;
	e[ptr] = edge(b, a, _c);
	head[b] = ptr++;
}
int dep[1000005];
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
int cur[1000005];
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
	scanf("%d%d", &n, &m);
	s = 1;
	t = get(n, m);
	for(int i = 1; i <= n; i++)
	{
		for(int j = 1; j < m; j++)
		{
			int x;
			scanf("%d", &x);
			add_edge(get(i, j), get(i, j + 1), x, x);
		}
	}
	for(int i = 1; i < n; i++)
	{
		for(int j = 1; j <= m; j++)
		{
			int x;
			scanf("%d", &x);
			add_edge(get(i, j), get(i + 1, j), x, x);
		}
	}
	for(int i = 1; i < n; i++)
	{
		for(int j = 1; j < m; j++)
		{
			int x;
			scanf("%d", &x);
			add_edge(get(i, j), get(i + 1, j + 1), x, x);
		}
	}
	printf("%d", run());
	return 0;
}
