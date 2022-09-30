#include <cstdio>
#include <cstring>
#define N 300
const int mod = 1e9 + 7;
int n;
int f[N + 5][N + 5][N + 5];
long long fac[N * 5 + 5];
long long finv[N * 5 + 5];
long long inv[N * 5 + 5];
int deg[N + 5];
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
void init()
{
	fac[0] = finv[0] = 1;
	inv[0] = 1;
	for(int i = 1; i <= N * 5; i++)
	{
		fac[i] = (fac[i - 1] * i) % mod;
		finv[i] = power(fac[i], mod - 2);
		inv[i] = power(i, mod - 2);
	}
}
long long c(int n, int m)
{
	if(n < m) return 0;
	if(n < 0 || m < 0) return 0;
	return fac[n] * (finv[m] * finv[n - m] % mod) % mod;
}
int main()
{
	init();
	scanf("%d", &n);
	bool loop = true;
	for(int i = 1; i <= n; i++)
	{
		scanf("%d", &deg[i]);
		if(deg[i] != 2) loop = false;
	}
	if(loop)
	{
		printf("%lld", fac[n - 1] * inv[2] % mod);
		return 0;
	}
	f[0][0][0] = 1;
	for(int i = 0; i < n; i++)
	{
		for(int j = 0; j <= n; j++)
		{
			for(int k = 0; k <= n; k++)
			{
				(f[i + 1][j][k] += 1ll * f[i][j][k] * finv[deg[i + 1] - 1] % mod) %= mod;
				if(deg[i + 1] >= 2)
				{
					(f[i + 1][j + 1][k + deg[i + 1] - 2] += 1ll * f[i][j][k] * c(k + deg[i + 1] - 2, deg[i + 1] - 2) % mod) %= mod;
				}
			}
		}
	}
	long long ans = 0;
	long long pinv = 1;
	for(int i = 3; i < n; i++)
	{
		for(int j = 0; j <= n; j++)
		{
			(ans += 1ll * f[n][i][j] * fac[n - i - 1] % mod * finv[j - 1] % mod * fac[i - 1] % mod * inv[2] % mod) %= mod;
		}
	}
	printf("%lld", ans);
	return 0;
}
