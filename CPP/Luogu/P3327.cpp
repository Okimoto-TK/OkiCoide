#include <cstdio>
#include <algorithm>
#define N 50000
int tot;
bool npr[N + 5];
int pr[N + 5];
int mu[N + 5];
int mus[N + 5];
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
		mus[i] = mus[i - 1] + mu[i];
	}
}
int sum[N + 5];
int t;
int main()
{
	mobius();
	for(int i = 1; i <= N; i++)
	{
		int l = 1, r;
		for(; l <= i; l = r + 1)
		{
			r = i / (i / l);
			sum[i] += (i / l) *  (r - l + 1);
		}
	}
	scanf("%d", &t);
	for(int i = 1; i <= t; i++)
	{
		int n, m;
		scanf("%d%d", &n, &m);
		int l = 1, r;
		int max = std::min(n, m);
		long long ans = 0;
		for(; l <= max; l = r + 1)
		{
			r = std::min(n / (n / l), m / (m / l));
			ans += 1ll * (mus[r] - mus[l - 1]) * sum[n / l] * sum[m / l];
		}
		printf("%lld\n", ans);
	}
}