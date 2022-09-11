#include <cstdio>
const int mod = 998244353;
long long power(long long x, int k)
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
int main()
{
	int T;
	for(scanf("%d", &T); T; T--)
	{
		int m;
		scanf("%d", &m);
		long long ans = 1;
		for(int i = 1; i <= m; i++)
		{
			long long p, q;
			scanf("%lld%lld", &p, &q);
			(ans *= (q * (p - 1) % mod * power(p, q - 1) % mod + power(p, q)) % mod) %= mod;
		}
		printf("%lld\n", ans);
	}
}