#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>
int head[105];
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
} e[100005];
int n, m;
int s, t;
int ptr;
inline void add_edge(int a, int b, int c)
{
	e[ptr] = edge(a, b, c);
	head[a] = ptr++;
	e[ptr] = edge(b, a, 0);
	head[b] = ptr++;
}
int dep[105];
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
int cur[105];
int dfs(int u, int f)
{
	if(u == t) return f;
	int fsum = 0;
	for(int i = cur[u]; i != -1; i = e[i].nxt)
	{
		int v = e[i].v;
		if(dep[v] == dep[u] + 1 && e[i].f > 0)
		{
			int _f = dfs(v, std::min(e[i].f, f));
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
inline void print()
{
	for(int i = 1; i <= m; i++)
	{
		for(int j = head[i]; j != -1; j = e[j].nxt)
		{
			if(e[j].f == 0 && e[j].v != n + 1)
			{
				printf("%d %d\n", i, e[j].v);
				break;
			}
		}
	}
}
int main()
{
	memset(head, -1, sizeof(head));
	scanf("%d%d", &m, &n);
	s = n + 1;
	t = n + 2;
	int u, v;
	for(int i = 1; i <= m; i++)
	{
		add_edge(s, i, 1);
	}
	for(int i = m + 1; i <= n; i++)
	{
		add_edge(i, t, 1);
	}
	for(scanf("%d%d", &u, &v); u != -1 && v != -1; scanf("%d%d", &u, &v))
	{
		add_edge(u, v, 1);
	}
	printf("%d\n", run());
	print();
	return 0;
}
