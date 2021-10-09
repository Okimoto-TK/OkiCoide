#include <cstdio>
#include <vector>
int n;
int dep[100005];
std::vector<int> g[100005];
void dfs(int u, int fa)
{
	int len = g[u].size();
	for(int i = 0; i < len; i++)
	{
		int v = g[u][i];
		if(v == fa) continue;
		dep[v] = dep[u] + 1;
		dfs(v, u);
	}
}
int main()
{
	scanf("%d", &n);
	for(int i = 1; i < n; i++)
	{
		int a, b;
		scanf("%d%d", &a, &b);
		g[a].push_back(b);
		g[b].push_back(a);
	}
	dep[1] = 1;
	dfs(1, 0);
	double ans = 0;
	for(int i = 1; i <= n; i++) ans += 1.0 / dep[i];
	printf("%lf", ans);
	return 0;
}
