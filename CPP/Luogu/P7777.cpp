#include <cstdio>
#include <cmath>
#include <algorithm>
int t;
int main()
{
	scanf("%d", &t);
	for(int i = 1; i <= t; i++)
	{
		long long n, p, q, ans = 0;
		scanf("%lld%lld%lld", &n, &p, &q);
		if(p == 0)
		{
			printf("0\n");
			continue;
		}
		int oe = n % 2;
		double mid = (1.0 * double(q) / double(p) - 1) / 2.0;
		if(mid < 1.0)
		{
			printf("%lld\n", n / 2 * q + oe * p);
			continue;
		}
		int _mid = (int)ceil(mid);
		if(_mid % 2 == oe) _mid++;
		if(_mid > n)
		{
			printf("%lld\n", (n + 1) * n / 2 * p);
			continue;
		}
		ans = (n - _mid + 1) / 2 * q;
		if(_mid > 3)
		{
			ans += (1 + _mid - 3) * (_mid - 3) / 2 * p;
		}
		if(_mid > 2)
		{
			ans += std::min((2 * _mid - 3) * p, q);
		}
		if(_mid == 2) ans += p;
		printf("%lld\n", ans);
	}
	return 0;
}

