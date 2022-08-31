#include <cstdio>
#include <algorithm>
#define N 10000000
const int mod = 20101009;
int tot;
bool npr[N + 5];
int pr[N + 5];
int mu[N + 5];
long long f[N + 5];
long long g[N + 5];
inline void qmod(long long & x)
{
	x %= mod;
}
void esv()
{
	mu[1] = 1;
	for(int i = 2; i <= N; i++)
	{
		if(!npr[i])
		{
			pr[++tot] = i;
			mu[i] = -1;
		}
		for(int j = 1; j <= tot && i * pr[j] <= N; j++)
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
		if(mu[i] == 0) continue;
		for(int j = 1; i * j <= N; j++)
		{
			qmod(f[i * j] += mu[i] * i);
		}
	}
	for(int i = 1; i <= N; i++)
	{
		qmod(f[i] *= i);
		qmod(g[i] = g[i - 1] + f[i]);
	}
}
long long sum[N + 5];
void init()
{
	for(int i = 1; i <= N; i++)
	{
		qmod(sum[i] = sum[i - 1] + i);
	}
}
int main()
{
	esv();
	init();
	int n, m;
	scanf("%d%d", &n, &m);
	int l = 1, r;
	int max = std::min(n, m);
	long long ans = 0;
	for(; l <= max; l = r + 1)
	{
		r = std::min(n / (n / l), m / (m / l));
		(ans += (g[r] - g[l - 1]) * sum[n / l] % mod * sum[m / l] % mod) %= mod;
	}
	printf("%lld", (ans + mod) % mod);
	return 0;
}