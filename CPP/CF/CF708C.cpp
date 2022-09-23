#include <cstdio>
#include <vector>
#include <algorithm>
#define N 400000
int n;
int a[N + 5];
int siz[N + 5];
int son[N + 5];
bool ans[N + 5];
std::vector<int> vec[N + 5];
int root;
int min = 0x3f3f3f3f;
void dfs1(int u, int fa)
{
	int max = 0;
	siz[u] = 1;
	for(auto v : vec[u])
	{
		if(v == fa) continue;
		dfs1(v, u);
		siz[u] += siz[v];
		max = std::max(max, siz[v]);
		if(siz[v] > siz[son[u]])
		{
			son[u] = v;
		}
	}
	max = std::max(max, n - siz[u]);
	if(max < min)
	{
		min = max;
		root = u;	
	}
}
int f[N + 5][2];
void dfs2(int u, int fa)
{
	for(auto v : vec[u])
	{
		if(v == fa) continue;
		dfs2(v, u);
		if(siz[v] > n/2) continue;
		if(siz[v] > f[u][0])
		{
			f[u][1] = f[u][0];
			f[u][0] = siz[v];
		}
		else if(siz[v] > f[u][1])
		{
			f[u][1] = siz[v];
		}
	}
	//printf("dfs2:%d %d %d\n", u, f[u][0], f[u][1]);
}
int g[N + 5];
int max[N + 5][2];
void dfs3(int u, int fa, int maxx)
{
	if(n - siz[u] <= n / 2)
	{
		maxx = std::max(maxx, n - siz[u]);
	}
	for(auto v : vec[u])
	{
		if(v == fa) continue;
		//printf("dfs3:%d %d %d %d\n", u, v, f[u][0], f[u][1]);
		if(siz[v] == f[u][0])
		{
			g[v] = std::max(maxx, f[u][1]);
		}
		else
		{
			g[v] = std::max(maxx, f[u][0]);
		}
		dfs3(v, u, g[v]);
	}
	//printf("%d %d\n", u, g[u]);
}
int main()
{
	scanf("%d", &n);
	for(int i = 1; i < n; i++)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		vec[u].push_back(v);
		vec[v].push_back(u);
	}
	dfs1(1, 0);
	//printf("root:%d\n", root);
	dfs1(root, 0);
	dfs2(root, 0);
	dfs3(root, 0, 0);
	for(int i = 1; i <= n; i++)
	{
		if(i == root) ans[i] = true;
		else
		{
			if(n - siz[i] - g[i] <= n / 2) ans[i] = true;
		}
	}
	for(int i =1; i <= n; i++)
	{
		printf("%d ", ans[i] ? 1 : 0);
	}
	return 0;
}
