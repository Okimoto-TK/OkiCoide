#include <cstdio>
#include <vector>
#define P 998244353
int id, n, m;
long long f[1000005];
std::vector<int> g[1000005];
int main()
{
	scanf("%d%d%d", &id, &n, &m);
	for(int i = 1; i <= m; i++)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		g[u].push_back(v);
	}
	f[0] = 0;
	for(int i = 1; i <= n; i++)
	{
		long long k = g[i].size();
		long long t = 0;
		for(int j = 0; j < k; j++)
		{
			int v = g[i][j];
			(t += f[i - 1] - f[v - 1]) %= P;
		}
		(f[i] = f[i - 1] + (k + 1) + t) %= P;
	}
	printf("%lld", (f[n] + P) % P);
	return 0;
}
