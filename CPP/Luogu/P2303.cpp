#include <cstdio>
#include <cmath>
#include <algorithm>
#include <vector>
long long phi(long long x)
{
	long long phi = 1;
	long long max = sqrt(x);
	for(long long i = 2; x != 1 && i <= max; i++)
	{
		if(x % i == 0)
		{
			x /= i;
			phi *= (i - 1);
			while(x % i == 0)
			{
				x /= i;
				phi *= i;
			}
		}
	}
	if(x != 1)
	{
		phi *= (x - 1);
	}
	return phi;
}
int main()
{
	long long n;
	scanf("%lld", &n);
	long long max = sqrt(n);
	long long ans = 0;
	for(long long i = 1; i <= max; i++)
	{
		if(n % i == 0)
		{
			ans += (n / i) * phi(i);
			//printf("%lld %lld\n", i, phi(i));
			if(n / i != i)
			{
				ans += i * phi(n / i);
				//printf("%lld %lld\n", n / i, phi(n / i));
			}
		}
	}
	printf("%lld", ans);
	return 0;
}