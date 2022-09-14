#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#define N 250000
struct Edge
{
	int u, v;
	long long w;
} e[N * 2 + 5];
int n, m, p, top, pool;
int dfn[N + 5];
int dep[N + 5];
int rpr[N + 5];
int lca[N + 5][20];
int h[N + 5];
int sta[N + 5];
bool spe[N + 5];
long long min[N + 5][20];
std::vector<int> vec[N + 5];
std::vector<int> g[N + 5];
void dfs(int u, int fa, long long val)
{
	dep[u] = dep[fa] + 1;
	dfn[u] = ++pool;
	rpr[pool] = u;
	lca[u][0] = fa;
	min[u][0] = val;
	for(int i = 1; i <= 19; i++)
	{
		lca[u][i] = lca[lca[u][i - 1]][i - 1];
		min[u][i] = std::min(min[u][i - 1], min[lca[u][i - 1]][i - 1]);
	}
	for(auto i : vec[u])
	{
		if(e[i].v == fa) continue;
		dfs(e[i].v, u, e[i].w);
	}
}
bool cmp(int x, int y)
{
	return dfn[x] < dfn[y];
}
int Lca(int x, int y)
{
	if(dep[x] < dep[y])
	{
		std::swap(x, y);
	}
	for(int i = 19; i >= 0; i--)
	{
		if(dep[lca[x][i]] >= dep[y])
		{
			x = lca[x][i];
		}
	}
	if(x == y) return x;
	for(int i = 19; i >= 0; i--)
	{
		if(lca[x][i] != lca[y][i])
		{
			x = lca[x][i];
			y = lca[y][i];
		}
	}
	return lca[x][0];
}
void build(int k)
{
	std::sort(h + 1, h + 1 + k, cmp);
	top = 0;
	sta[++top] = 1;
	g[1].clear();
	spe[1] = false;
	for(int i = 1; i <= k; i++)
	{
		int c = Lca(h[i], sta[top]);
		if(c != sta[top])
		{
			while(dfn[c] < dfn[sta[top - 1]])
			{
				g[sta[top - 1]].push_back(sta[top]);
				g[sta[top]].push_back(sta[top - 1]);
				top--;
			}
			if(dfn[c] != dfn[sta[top - 1]])
			{
				g[c].clear();
				spe[c] = false;
				g[c].push_back(sta[top]);
				g[sta[top]].push_back(c);
				sta[top] = c;
			}
			else
			{
				g[c].push_back(sta[top]);
				g[sta[top]].push_back(c);
				top--;
			}
		}
		g[h[i]].clear();
		spe[h[i]] = true;
		sta[++top] = h[i];
	}
	for(int i = 1; i < top; i++)
	{
		g[sta[i]].push_back(sta[i + 1]);
		g[sta[i + 1]].push_back(sta[i]);
	}
}
long long W(int x, int y)
{
	if(dep[x] < dep[y])
	{
		std::swap(x, y);
	}
	long long re = 0x3f3f3f3f3f3f3f3f;
	for(int i = 19; i >= 0; i--)
	{
		if(dep[lca[x][i]] >= dep[y])
		{
			re = std::min(re, min[x][i]);
			x = lca[x][i];
		}
	}
	return re;
}
long long dp(int u, int fa)
{
	//printf("%d %d\n", u, fa);
	long long re = 0;
	for(auto v : g[u])
	{
		if(v == fa) continue;
		if(spe[v])
		{
			re += W(v, u);
		}
		else
		{
			re += std::min(W(v, u), dp(v, u));
		}
	}
	return re;
}
int main()
{
	memset(min, 0x3f, sizeof(min));
	scanf("%d", &n);
	for(int i = 1; i < n; i++)
	{
		int u, v, w;
		scanf("%d%d%d", &u, &v, &w);
		e[++p].u = u;
		e[p].v = v;
		e[p].w = w;
		vec[u].push_back(p);
		e[++p].v = u;
		e[p].u = v;
		e[p].w = w;
		vec[v].push_back(p);
	}
	dfs(1, 0, 0);
	//printf("%lld\n", W(2, 10));
	scanf("%d", &m);
	for(int i = 1; i <= m; i++)
	{
		int k;
		scanf("%d", &k);
		for(int j = 1; j <= k; j++)
		{
			scanf("%d", &h[j]);
		}
		build(k);
		printf("%lld\n", dp(1, 0));
	}
	return 0;
}