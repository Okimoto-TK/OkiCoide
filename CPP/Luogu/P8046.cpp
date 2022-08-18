#include <cstdio>
#include <algorithm>
long long n;
int k, q;
long long power(long long x, int k)
{
	long long r = 1;
	while(k)
	{
		if(k & 1)
		{
			r *= x;
		}
		x *=x ;
		k >>= 1;
	}
	return r;
}
int getDep(long long x)
{
	int dep;
	long long s;
	for(dep = 1, s = 1; s < x; s += power(k, dep++));
	return dep;
}
int main()
{
	scanf("%lld%d%d", &n, &k, &q);
	for(int i = 1; i <= q; i++)
	{
		long long x, y;
		scanf("%lld%lld", &x, &y);
		if(k == 1)
		{
			printf("%lld\n", std::abs(y - x));
		    continue;
		}
		int depx = getDep(x);
		int depy = getDep(y);
		int o = depx + depy;
		x -= (power(k, depx - 1) - 1) / (k - 1);
		y -= (power(k, depy - 1) - 1) / (k - 1);
		//printf("%d %d %d %d\n", x, y, depx, depy);
		while(depx != depy || x != y)
		{
			if(depx < depy)
			{
				std::swap(x, y);
				std::swap(depx, depy);
			}
			depx--;
			x = (x + k - 1) / k;
		}
		printf("%d\n", o - 2 * depx);
	}
	return 0;
}