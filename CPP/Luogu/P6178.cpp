#include <cstdio>
#include <algorithm>
const int mod = 1e9 + 7;
int n, m, t;
long long kir[305][305];
void add_edge(int u, int v, int w)
{
	(kir[u][v] -= w) %= mod;
	(kir[v][v] += w) %= mod;
}
long long det()
{
	int f = 1;
	for(int i = 1; i <= n; i++)
	{
		for(int j = i + 1; j <= n; j++)
		{
			while(kir[i][i])
			{
				long long d = kir[j][i] / kir[i][i];
				for(int k = i; k <= n; k++)
				{
					kir[j][k] = (kir[j][k] - kir[i][k] * d % mod) % mod;
				}
				std::swap(kir[i], kir[j]);
				f *= -1;
			}
			std::swap(kir[i], kir[j]);
			f *= -1;
		}
	}
	long long ans = 1;
	for(int i = 1; i <= n; i++)
	{
		ans = ans * kir[i][i] % mod;
	}
	return ans * f;
}
int main()
{
	scanf("%d%d%d", &n, &m, &t);
	for(int i = 1; i <= m; i++)
	{
		int u, v, w;
		scanf("%d%d%d", &u, &v, &w);
		u--, v--;
		add_edge(u, v, w);
		if(t == 0)
		{
			add_edge(v, u, w);
		}
	}
	n -= 1;
	printf("%lld", (det() % mod + mod) % mod);
	return 0;
}
