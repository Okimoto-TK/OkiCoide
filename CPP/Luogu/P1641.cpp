#include <cstdio>
const int mod = 20100403;
long long cat[1000005];
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
long long comb(int m, int n)
{
	long long r = 1;
	for(int i = 0; i < n; i++)
	{
		(r *= (m - i)) %= mod;
	}
	for(int i = n; i >= 1; i--)
	{
		(r *= power(i, mod - 2)) %= mod;
	}
	return r;
}
int n, m;
int main()
{
	scanf("%d%d", &n, &m);
	long long ans = comb(n + m, n) - comb(n + m, m - 1);
	printf("%lld", (ans % mod + mod) % mod);
	return 0;
}