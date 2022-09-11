#include <cstdio>
#define N 100000
const int mod = 1e9 + 7;
long long power(long long x, int k)
{
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
long long fac[N + 5];
long long inv[N + 5];
long long f[N + 5];
long long g[N + 5];
int main()
{
	fac[0] = inv[0] = 1;
	for(int i = 1; i <= N; i++)
	{
		fac[i] = fac[i - 1] * i % mod;
		inv[i] = power(fac[i], mod - 2);
	}
	int n;
	scanf("%d", &n);
	for(int d = 0; d < n; d++)
	{
		f[d] = fac[d] * fac[n] % mod * inv[d + 1] % mod;
	}
	for(int d = 1; d < n; d++)
	{
		g[d] = g[d - 1] + f[d];
	}
	long long ans = 0;
	for(int i = 1; i <= n; i++)
	{
		long long a;
		scanf("%lld", &a);
		(ans += (f[0] + g[i - 1] + g[n - i]) % mod * a % mod) %= mod;
	}
	printf("%lld", ans);
	return 0;
}