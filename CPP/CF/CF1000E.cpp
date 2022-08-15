#include <cstdio>
#include <cstring>
#include <algorithm>
#define N 300005
int n, m, p, pool, buf;
int head[N << 1];
struct Edge
{
	int u, v, nxt;
} e[N << 2];
void add_edge(int u, int v)
{
	e[p].u = u;
	e[p].v = v;
	e[p].nxt = head[u];
	head[u] = p++;
}
int dfn[N];
int low[N];
bool cut[N << 2];
void tarjan(int u, int fa)
{
	dfn[u] = low[u] = ++pool;
	for(int i = head[u]; i != -1; i = e[i].nxt)
	{
		int v = e[i].v;
		if(v == fa) continue;
		if(!dfn[v])
		{
			tarjan(v, u);
			low[u] = std::min(low[u], low[v]);
			if(dfn[u] < low[v])
			{
				cut[i] = cut[i ^ 1] = true;
			}
		}
		else
		{
			low[u] = std::min(low[u], dfn[v]);
		}
	}
}
int s[N];
void init()
{
	for(int i = 0; i < N; i++)
	{
		s[i] = i;
	}
}
int find(int x)
{
	if(s[x] == x) return x;
	return s[x] = find(s[x]);
}
void merge(int x, int y)
{
	if(find(x) == find(y)) return;
	s[find(x)] = find(y);
}
int bel[N];
int to[N];
void shrink()
{
	init();
	for(int u = 1; u <= n; u++)
	{
		for(int i = head[u]; i != -1; i = e[i].nxt)
		{
			if(cut[i]) continue;
			merge(u, e[i].v);
		}
	}
	for(int i = 1; i <= n; i++)
	{
		if(to[find(i)] == 0)
		{
			to[find(i)] = ++buf;
		}
		bel[i] = to[find(i)];
	}
	for(int u = 1; u <= n; u++)
	{
		for(int i = head[u]; i != -1; i = e[i].nxt)
		{
			if(cut[i])
			{
				add_edge(bel[u] + n, bel[e[i].v] + n);
			}
		}
	}
}
int f[N << 1];
int g[N << 1];
bool vis[N << 1];
void dfs(int u, int fa)
{
	vis[u] = true;
	for(int i = head[u]; i != -1; i = e[i].nxt)
	{
		int v = e[i].v;
		if(v == fa) continue;
		dfs(v, u);
		f[u] = std::max(f[u], g[u] + g[v] + 1);
		g[u] = std::max(g[u], g[v] + 1);
	}
}
int main()
{
	memset(head, -1, sizeof(head));
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= m; i++)
	{
		int x, y;
		scanf("%d%d", &x, &y);
		add_edge(x, y);
		add_edge(y, x);
	}
	for(int i = 1; i <= n; i++)
	{
		if(!dfn[i])
		{
			tarjan(i, 0);
		}
	}
	shrink();
	for(int i = n + 1; i <= n + buf; i++)
	{
		if(!vis[i])
		{
			dfs(i, 0);
		}
	}
	int ans = 0;
	for(int i = n + 1; i <= n + buf; i++)
	{
		ans = std::max(ans, f[i]);
	}
	printf("%d", ans);
	return 0;
}