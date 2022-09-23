#include <cstdio>
#include <vector>
#include <algorithm>
#define N 300000
int n;
std::vector<int> vec[N + 5];
int son[N + 5];
int siz[N + 5];
int spr[N + 5];
void dfs1(int u, int fa)
{
	siz[u] = 1;
	spr[u] = fa;
	for(auto v : vec[u])
	{
		if(v == fa) continue;
		dfs1(v, u);
		siz[u] += siz[v];
		if(siz[v] > siz[son[u]])
		{
			son[u] = v;
		}
	}
}
int ans[N + 5];
int min[N + 5];
void dfs2(int u, int fa)
{
	ans[u] = u;
	min[u] = siz[son[u]];
	for(auto v : vec[u])
	{
		if(v == fa) continue;
		dfs2(v, u);
	}
	if(son[u] == 0) return;
	int x = ans[son[u]];
	while(x != u)
	{
		int tmp = std::max(siz[u] - siz[x], siz[son[x]]);
		if(tmp < min[u])
		{
			min[u] = tmp;
			ans[u] = x;
		}
		if(siz[u] - siz[x] < siz[son[x]]) break;
		x = spr[x];
	}
}
int main()
{
	scanf("%d", &n);
	int q;
	scanf("%d", &q);
	for(int i = 2; i <= n; i++)
	{
		int v;
		scanf("%d", &v);
		vec[v].push_back(i);
	}
	dfs1(1, 0);
	dfs2(1, 0);
	for(int i = 1; i <= q; i++)
	{
		int x;
		scanf("%d", &x);
		printf("%d\n", ans[x]);
	}
	return 0;
}
