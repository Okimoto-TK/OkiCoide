#include <cstdio>
#include <cstring>
#include <algorithm>]
#define int long long
int n, m, k;
int p[1000005];
int dom[105];
long long w[105][505];
long long f[105][505];
signed main()
{
	scanf("%lld%lld%lld", &n, &m, &k);
	for(int i = 1; i <= n; i++)
	{
		scanf("%lld", &p[i]);
		dom[p[i]]++;
	}
	for(int i = 1; i <= m; i++)
	{
		for(int j = 0; j <= k; j++)
		{
			if(j == 0)
			{
				w[i][j] = (1 + dom[i]) * dom[i] / 2;
			}
			else
			{
				long long t = dom[i] / (j + 1);
				long long re = dom[i] - t * (j + 1);
				w[i][j] = (j + 1) * (1 + t) * t / 2 + (t + 1) * re;
			}
			//printf("%d %d %d\n", i, j, w[i][j]);
		}
	}
	memset(f, 0x3f, sizeof(f));
	for(int i = 0; i <= k; i++) f[0][i] = 0;
	for(int i = 1; i <= m; i++)
	{
		for(int v = k; v >= 0; v--)
		{
			for(int j = 0; j <= v; j++)
			{
				f[i][v] = std::min(f[i][v], f[i - 1][v - j] + w[i][j]); 
			}
		}
	}
	long long ans = 0x3f3f3f3f3f3f3f3f;
	for(int i = 0; i <= k; i++)
	{
		ans = std::min(ans, f[m][i]);
	}
	printf("%lld", ans);
	return 0;
}
