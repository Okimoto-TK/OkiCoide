#include <cstdio>
#include <vector>
int n;
std::vector<int> g[200005];
long long cnt[2][200005];
long long sum[200005];
long long ans;
long long odd;
void dfs(int u, int fa)
{
	int len = g[u].size();
	cnt[0][u] = 1;
	for(int i = 0; i < len; i++)
	{
		int v = g[u][i];
		if(v == fa) continue;
		dfs(v, u);
		odd += cnt[0][u] * cnt[0][v] + cnt[1][u] * cnt[1][v];
		sum[u] += sum[v] + (cnt[0][v] + cnt[1][v]);
		cnt[0][u] += cnt[1][v];
		cnt[1][u] += cnt[0][v];
	}
	for(int i = 0; i < len; i++)
	{
		int v = g[u][i];
		if(v == fa) continue;
		ans += (cnt[0][u] + cnt[1][u] - cnt[0][v] - cnt[1][v]) * (sum[v] + cnt[0][v] + cnt[1][v]);
	}
}
int main()
{
	scanf("%d", &n);
	for(int i = 1; i < n; i++)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		g[u].push_back(v);
		g[v].push_back(u);
	}
	dfs(1, 0);
	printf("%lld", (ans + odd) / 2);
	return 0;
}
