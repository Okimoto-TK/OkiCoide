#include <cstdio>
#include <algorithm>
#define N 10000000
int tot;
bool npr[N + 5];
int pr[N + 5];
int mu[N + 5];
int val[N + 5];
long long sum[N + 5];
void mobius()
{
	mu[1] = 1;
	for(int i = 2; i <= N; i++)
	{
		if(!npr[i])
		{
			pr[++tot] = i;
			mu[i] = -1;
		}
		for(int j = 1; j <= tot && pr[j] * i <= N; j++)
		{
			npr[i * pr[j]] = true;
			if(i % pr[j] == 0)
			{
				mu[i * pr[j]] = 0;
				break;
			}
			mu[i * pr[j]] = -mu[i];
		}
	}
	for(int i = 1; i <= N; i++)
	{
		for(int j = 1; j <= tot && pr[j] * i <= N; j++)
		{
			val[i * pr[j]] += mu[i];
		}
	}
	for(int i = 1; i <= N; i++)
	{
		sum[i] = sum[i - 1] + val[i];
	}
}
int T, n, m;
int main()
{
	mobius();
	for(scanf("%d", &T); T; T--)
	{
		scanf("%d %d", &n, &m);
		int max = std::min(n, m);
		int l = 1, r;
		long long ans = 0;
		for(; l <= max; l = r + 1)
		{
			r = std::min(n / (n / l), m / (m / l));
			ans += (sum[r] - sum[l - 1]) * (n / l) * (m / l);
		}
		printf("%lld\n", ans);
	}
	return 0;
}