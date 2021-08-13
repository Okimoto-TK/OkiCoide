#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>
#define INF 0x3f3f3f3f
struct edge
{
	int u;
	int v;
	int f;
	int nxt;
	edge() { u = v = f = nxt = -1; }
	edge(int a, int b, int c, int *head)
	{
		u = a;
		v = b;
		f = c;
		nxt = head[a];
	}
};
int m, n, ptr, s, t;
int dx[] = {0, -1, 0};
int dy[] = {0, 0, -1};
int a[105][105];
int head[10005];
int cur[10005];
int dep[10005];
edge e[1000005];
inline void add_edge(int a, int b, int c)
{
	e[ptr] = edge(a, b, c, head);
	head[a] = ptr++;
	e[ptr] = edge(b, a, 0, head);
	head[b] = ptr++;
}
inline int getId(int x, int y)
{
	return (x - 1) * n + y;
}
inline bool check(int x, int y)
{
	return x >= 1 && x <= m && y >= 1 && y <= n;
}
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
	int total = 0;
	memset(head, -1, sizeof(head));
	scanf("%d%d", &m, &n);
	s = 2 * m * n + 1;
	t = s + 1;
	for(int i = 1; i <= m; i++)
	{
		for(int j = 1; j <= n; j++)
		{
			scanf("%d", &a[i][j]);
			total += a[i][j];
			add_edge(getId(i, j), getId(i, j) + n * m, a[i][j]);
			if((i + j) & 1) add_edge(getId(i, j) + n * m, t, INF);
			else add_edge(s, getId(i, j), INF);
			for(int k = 1; k <= 2; k++)
			{
				int x = i + dx[k];
				int y = j + dy[k];
				if(check(x, y))
				{
					add_edge(getId(x, y) + n * m, getId(i, j), INF);
					add_edge(getId(i, j) + n * m, getId(x, y), INF);
				}
			}
		}
	}
	printf("%d", total - run());
	return 0;
}
