#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>
#define N 200005
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
} e[8 * N];
int n, m, s, t, pool, ptr, sum;
int dx[] = {0, 1, 0};
int dy[] = {0, 0, 1};
inline int getId(int x, int y) { return (x - 1) * m + y; }
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
int main()
{
	memset(head, -1, sizeof(head));
	scanf("%d%d", &n, &m);
	pool = n * m;
	s = ++pool;
	t = ++pool;
	for(int i = 1; i <= n; i++)
	{
		for(int j = 1; j <= m; j++)
		{
			int art;
			scanf("%d", &art);
			sum += art;
			add_edge(s, getId(i, j), art);
		}
	}
	for(int i = 1; i <= n; i++)
	{
		for(int j = 1; j <= m; j++)
		{
			int sci;
			scanf("%d", &sci);
			sum += sci;
			add_edge(getId(i, j), t, sci);
		}
	}
	for(int k = 1; k <= 2; k++)
	{
		for(int i = 1; i <= ((k == 1) ? n - 1 : n); i++)
		{
			for(int j = 1; j <= ((k == 2) ? m - 1 : m); j++)
			{
				int sart;
				scanf("%d", &sart);
				++pool;
				add_edge(s, pool, sart);
				sum += sart;
				add_edge(pool, getId(i, j), INF);
				add_edge(pool, getId(i + dx[k], j + dy[k]), INF);
			}
		}
		for(int i = 1; i <= ((k == 1) ? n - 1 : n); i++)
		{
			for(int j = 1; j <= ((k == 2) ? m - 1 : m); j++)
			{
				int ssci;
				scanf("%d", &ssci);
				++pool;
				add_edge(pool, t, ssci);
				sum += ssci;
				add_edge(getId(i, j), pool, INF);
				add_edge(getId(i + dx[k], j + dy[k]), pool, INF);
			}
		}
	}
	printf("%d", sum - run());
	return 0;
}
