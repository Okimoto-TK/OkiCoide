#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>
#define INF 0x3f3f3f3f
int head[2000];
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
} e[4000000];
int n, m, s, t, ptr;
int a[50][50];
int dx[] = {0, -1, 0};
int dy[] = {0, 0, -1};
inline bool valid(int x, int y)
{
	return x >= 1 && x <= n && y >= 1 && y <= m;
}
inline int get(int x, int y)
{
	return (x - 1) * m + y;
}
inline void add_edge(int a, int b, int c)
{
	e[ptr] = edge(a, b, c);
	head[a] = ptr++;
	e[ptr] = edge(b, a, 0);
	head[b] = ptr++;
}
int dep[2000];
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
int cur[2000];
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
		memcpy(cur, head, sizeof(head));
		ans += dfs(s, INF);
	}
	return ans;
}
int main()
{
	memset(head, -1, sizeof(head));
	scanf("%d%d", &n, &m);
	s = n * m * 2 + 1;
	t = s + 1;
	for(int i = 1; i <= n; i++)
	{
		for(int j = 1; j <= m; j++)
		{
			scanf("%d", &a[i][j]);
			if(a[i][j] == 0)
			{
				add_edge(get(i, j), get(i, j) + n * m, INF);
				add_edge(s, get(i, j), INF);
			}
			else
			{
				add_edge(get(i, j), get(i, j) + n * m, std::max(0, a[i][j]));
			}
			for(int k = 1; k <= 2; k++)
			{
				if(valid(i + dx[k], j + dy[k]))
				{
					add_edge(get(i, j) + n * m, get(i + dx[k], j + dy[k]), INF);
					add_edge(get(i + dx[k], j + dy[k]) + n * m, get(i, j), INF);
				}
			}
		}
	}
	for(int i = 1; i <= n; i++)
	{
		add_edge(get(i, 1) + n * m, t, INF);
		add_edge(get(i, m) + n * m, t, INF);
	}
	for(int i = 1; i <= m; i++)
	{
		add_edge(get(1, i) + n * m, t, INF);
		add_edge(get(n, i) + n * m, t, INF);
	}
	printf("%d", run());
	return 0;
}
