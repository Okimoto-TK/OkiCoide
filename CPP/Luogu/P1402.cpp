#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>
int head[1005];
struct edge
{
	int u;
	int v;
	int f;
	int nxt;
	edge() { u = v = f = nxt = -1; }
	edge(int a, int b, int c)
	{
		u = a;
		v = b;
		f = c;
		nxt = head[a];
	}
} e[1000005];
int n, p, q;
int ptr;
int s, t;
inline void add_edge(int a, int b, int c)
{
	e[ptr] = edge(a, b, c);
	head[a] = ptr++;
	e[ptr] = edge(b, a, 0);
	head[b] = ptr++;
}
int dep[1005];
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
int cur[1005];
int dfs(int u, int f)
{
	if(u == t) return f;
	int fsum = 0;
	for(int i = cur[u]; i != -1; i = e[i].nxt)
	{
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
		memcpy(cur, head, sizeof(head));
		ans += dfs(s, 0x3f3f3f3f);
	}
	return ans;
}
int main()
{
	memset(head, -1, sizeof(head));
	scanf("%d%d%d", &n, &p, &q);
	s = n + p + q + 1 + n;
	t = s + 1;
	for(int i = 1; i <= p; i++) add_edge(s, i, 1);
	for(int i = p + 1; i <= p + n; i++) add_edge(i, i + n, 1);
	for(int i = p + n * 2 + 1; i <= p + n * 2 + q; i++) add_edge(i, t, 1);
	for(int i = 1; i <= n; i++)
	{
		for(int j = 1; j <= p; j++)
		{
			int y;
			scanf("%d", &y);
			if(y == 1) add_edge(j, i + p, 1);
		}
	}
	for(int i = 1; i <= n; i++)
	{
		for(int j = 1; j <= q; j++)
		{
			int y;
			scanf("%d", &y);
			if(y == 1) add_edge(i + p + n, j + p + 2 * n, 1);
		}
	}
	printf("%d", run());
	return 0;
}
