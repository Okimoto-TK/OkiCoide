#include <cstdio>
#include <algorithm>
#define N 1000000
const int mod = 1000000007;
int tot;
bool npr[N + 5];
int pr[N + 5];
int mu[N + 5];
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
}
long long f[N + 5];
long long inv[N + 5];
long long g[N + 5];
long long prod[N + 5];
long long pinv[N + 5];
long long power(long long x, long long k)
{
	k %= (mod - 1);
	long long r = 1;
	while(k)
	{
		if(k&1)
		{
			(r *= x) %= mod;
		}
		(x *= x) %= mod;
		k >>= 1;
	}
	return r;
}
void init()
{
	f[1] = f[2] = g[1] = g[2] = inv[1] = inv[2] = 1;
	for(int i = 3; i <= N; i++)
	{
		f[i] = (f[i - 1] + f[i - 2]) % mod;
		inv[i] = power(f[i], mod - 2);
	}
	for(int i = 1; i <= N; i++) g[i] = 1;
	for(int t = 1; t <= N; t++)
	{
		for(int d = 1; d * t <= N; d++)
		{
			if(mu[d] == 0) continue;
			if(mu[d] == -1)
			{
				(g[d * t] *= inv[t]) %= mod;
			}
			else
			{
				(g[d * t] *= f[t]) %= mod;
			}
		}
	}
	prod[0] = 1;
	pinv[0] = 1;
	for(int i = 1; i <= N; i++)
	{
		prod[i] = prod[i - 1] * g[i] % mod;
		pinv[i] = power(prod[i], mod - 2);
	}
}
int T;
int main()
{
	esv();
	init();
	for(scanf("%d", &T); T; T--)
	{
		int n, m;
		scanf("%d%d", &n, &m);
		int max = std::min(n, m);
		int l = 1, r;
		long long ans = 1;
		for(; l <= max; l = r + 1)
		{
			r = std::min(n / (n / l), m / (m / l));
			(ans *= power(prod[r] * pinv[l - 1] % mod, 1ll * (n / l) * (m / l))) %= mod;
		}
		printf("%lld\n", ans);
	}
	return 0;
}