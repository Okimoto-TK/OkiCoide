#include <cstdio>
#include <vector>
#include <algorithm>
int n, t, ans;
struct edge
{
	int v;
	int w;
	edge(int x, int y)
	{
		v = x;
		w = y;
	}
	edge()
	{
		v = w = 0;
	}
};
std::vector<edge> g[20005];
int d[20005];
void dfs(int u, int fa)
{
	int len = g[u].size();
	d[u] = 0;
	for(int i = 0; i < len; i++)
	{
		int v = g[u][i].v;
		int w = g[u][i].w;
		if(v == fa) continue;
		dfs(v, u);
		if(d[v] + w >= t)
		{
			d[v] = 0;
			ans++;
		}
		d[u] = std::max(d[u], d[v] + w);
	}
}
int main()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
	{
		int k;
		scanf("%d", &k);
		for(int j = 1; j <= k; j++)
		{
			edge e;
			scanf("%d%d", &e.v, &e.w);
			g[i].push_back(e);
		}
	}
	scanf("%d", &t);
	for(int i = 1; i <= n; i++)
	{
		int len = g[i].size();
		for(int j = 0; j < len; j++)
		{
			int k = g[i][j].w;
			if(k >= t)
			{
				printf("No solution.");
				return 0;
			}
		}
	}
	dfs(1, 0);
	printf("%d", ans);
	return 0;
}
