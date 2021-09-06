#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>
int head[20005];
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
} e[400000];
int n, m, k, s, t, ptr, pool;
int l[105];
int lb[105];
int c[105];
int cb[105];
bool a[105][105];
inline void add_edge(int a, int b, int c)
{
	e[ptr] = edge(a, b, c);
	head[a] = ptr++;
	e[ptr] = edge(b, a, 0);
	head[b] = ptr++;
}
int dep[20005];
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
int cur[20005];
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
	scanf("%d%d%d", &m, &n, &k);
	s = 1;
	t = 2;
	for(int i = 1; i <= m; i++)
	{
		scanf("%d", &l[i]);	
	}
	for(int j = 1; j <= n; j++)
	{
		scanf("%d", &c[j]);
	}
	for(int i = 1; i <= k; i++)
	{
		int x, y;
		scanf("%d%d", &x, &y);
		a[x][y] = true;
		lb[x]++;
		cb[y]++;
	}
	for(int i = 1; i <= m; i++)
	{
		for(int j = 1; j <= n; j++)
		{
			if(!a[i][j]) add_edge(i + 2, j + m + 2, 1);
		}
	}
	for(int i = 1; i <= m; i++)
	{
		if(n - l[i] - lb[i] < 0)
		{
			printf("JIONG!");
			return 0;
		}
		add_edge(s, i + 2, n - l[i] - lb[i]);
	}
	for(int i = 1; i <= n; i++)
	{
		if(m - c[i] - cb[i] < 0)
		{
			printf("JIONG!");
			return 0;
		}
		add_edge(i + 2 + m, t, m - c[i] - cb[i]);
	}
	int b = 0;
	for(int i = 1; i <= m; i++) b += lb[i];
	printf("%d", n * m - b - run());
	return 0;
}
