#include <cstdio>
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
int n, m, k;
long long comb(int n, int m)
{
	if(m < 0) return 0;
	long long r = 1;
	for(int i = n - m + 1; i <= n; i++)
	{
		(r *= i) %= mod;
	}
	for(int i = 1; i <= m; i++)
	{
		(r *= power(i, mod - 2)) %= mod;
	}
	return r;
}
int main()
{
	scanf("%d%d%d", &n, &m, &k);
	if(m + k < n)
	{
		printf("0");
		return 0;
	}
	printf("%lld", ((comb(n + m, n) - comb(n + m, n - k - 1)) % mod + mod) % mod);
}