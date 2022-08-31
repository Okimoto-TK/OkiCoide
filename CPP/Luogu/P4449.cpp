#include <cstdio>
#include <algorithm>
#define N 5000000
const int mod = 1e9 + 7;
long long qpow(long long x, int k)
{
	long long r = 1;
	while(k)
	{
		if(k & 1)
		{
			(r *= x) %= mod;
		}
		(x *= x) %= mod;
		k >>= 1;
	}
	return r;
}
int T, k;
int tot;
bool npr[N + 5];
int pr[N + 5];
long long f[N + 5];
long long sum[N + 5];
void esv()
{
	f[1] = 1;
	for(int i = 2; i <= N; i++)
	{
		if(!npr[i])
		{
			pr[++tot] = i;
			f[i] = qpow(i, k) - 1;
		}
		for(int j = 1; j <= tot && i * pr[j] <= N; j++)
		{
			npr[i * pr[j]] = true;
			if(i % pr[j] == 0)
			{
				f[i * pr[j]] = (f[i] * (f[pr[j]] + 1)) % mod;
				break;
			}
			f[i * pr[j]] = (f[i] * f[pr[j]]) % mod;
		}
	}
	for(int i = 1; i <= N; i++)
	{
		sum[i] = (sum[i - 1] + f[i]) % mod;
	}
}
int main()
{
	scanf("%d%d", &T, &k);
	esv();
	for(int i = 1; i <= T; i++)
	{
		int n, m;
		scanf("%d%d", &n, &m);
		int l = 1, r;
		int max = std::min(n, m);
		long long ans = 0;
		for(; l <= max; l = r + 1)
		{
			r = std::min(n / (n / l), m / (m / l));
			(ans += (sum[r] - sum[l - 1]) * (n / l) % mod * (m / l)) %= mod;
		}
		printf("%lld\n", (ans + mod) % mod);
	}
	return 0;
}