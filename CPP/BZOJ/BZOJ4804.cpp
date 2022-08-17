#include <cstdio>
#define N 10000000
int tot;
bool npr[N + 5];
int pr[N + 5];
long long f[N + 5];
long long g[N + 5];
long long sum[N + 5];
void linsv()
{
	f[1] = 1;
	for(int i = 2; i <= N; i++)
	{
		if(!npr[i])
		{
			pr[++tot] = i;
			f[i] = i - 2;
			g[i] = 1;
		}
		for(int j = 1; j <= tot && i * pr[j] <= N; j++)
		{
			npr[i * pr[j]] = true;
			if(i % pr[j] == 0)
			{
				if(g[i] == 1)
				{
					if(pr[j] == 2) f[i * pr[j]] = 1 * f[i / pr[j]];
					else f[i * pr[j]] = f[i] * (pr[j] - 1) * (pr[j] - 1) / (pr[j] - 2);
				}
				else
				{
					f[i * pr[j]] = f[i] * pr[j];
				}
				g[i * pr[j]] = g[i] + 1;
				break;
			}
			f[i * pr[j]] = f[i] * (pr[j] - 2);
			g[i * pr[j]] = 1;
		}
	}
//	for(int i = 1; i <= 30; i++)
//	{
//		printf("%d %d\n", i, f[i]);
//	}
	for(int i = 1; i <= N; i++)
	{
		sum[i] = sum[i - 1] + f[i];
	}
}
int T, n;
int main()
{
	linsv();
	for(scanf("%d", &T); T; T--)
	{
		scanf("%d", &n);
		int l = 1, r;
		long long ans = 0;
		for(; l <= n; l = r + 1)
		{
			r = n / (n / l);
			ans += (sum[r] - sum[l - 1]) * (n / l) * (n / l);
		}
		printf("%lld\n", ans);
	}
}