#include <cstdio>
#include <cmath>
long long gcd(long long a, long long b)
{
	if(b == 0) return a;
	return gcd(b, a % b);
}
long long mu(long long x)
{
	long long max = sqrt(x);
	long long ans = 1;
	for(int i = 2; x != 1 && i <= max; i++)
	{
		if(x % i == 0)
		{
			ans *= -1;
			x /= i;
			if(x % i == 0)
			{
				return 0;
			}
		}
	}
	if(x != 1)
	{
		ans *= -1;
	}
	return ans;
}
int main()
{
	int T;
	for(scanf("%d", &T); T; T--)
	{
		long long a, m;
		scanf("%lld%lld", &a, &m);
		long long v = gcd(a, m);
		long long n = m / v;
		long long max = sqrt(n);
		long long ans = 0;
		for(int t = 1; t <= max; t++)
		{
			if(n % t == 0)
			{
				ans += mu(t) * (n / t);
				if(n / t != t)
				{
					ans += mu(n / t) * t;
				}
			}
		}
		printf("%lld\n", ans);
	}
}