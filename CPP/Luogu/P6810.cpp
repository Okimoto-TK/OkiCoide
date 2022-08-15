#include <cstdio>
#include <algorithm>
#define N 2000000
long long n, m, p, tot;
bool npr[N + 5];
int pr[N + 5];
int tau[N + 5];
int f[N + 5];
long long sum[N + 5];
void d()
{
	tau[1] = 1;
	for(int i = 2; i <= N; i++)
	{
		if(!npr[i])
		{
			pr[++tot] = i;
			tau[i] = 2;
			f[i] = 1;
		}
		for(int j = 1; j <= tot && pr[j] * i <= N; j++)
		{
			npr[i * pr[j]] = true;
			if(i % pr[j] == 0)
			{
				tau[i * pr[j]] = tau[i] / (1 + f[i]) * (2 + f[i]);
				f[i * pr[j]] = f[i] + 1;
				break;
			}
			tau[i * pr[j]] = 2 * tau[i];
			f[i * pr[j]] = 1;
		}
	}
	for(int i = 1; i <= N; i++)
	{
		sum[i] = sum[i - 1] + tau[i];
		//printf("%d %d\n", i, sum[i]);
	}
}
int main()
{
	scanf("%lld%lld%lld", &n, &m, &p);
	d();
	int max = std::min(n, m);
	long long ans = 0;
	for(int T = 1; T <= max; T++)
	{
		long long tmp1 = 0;
		long long tmp2 = 0;
		for(int i = 1; i <= n / T; i++)
		{
			(tmp1 += tau[i * T]) %= p;
		}
		for(int j = 1; j <= m / T; j++)
		{
			(tmp2 += tau[j * T]) %= p;
		}
		(ans += tmp1 % p * tmp2) %= p;
	}
	printf("%lld", ans);
	return 0;
}