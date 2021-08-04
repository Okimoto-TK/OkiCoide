#include <cstdio>
#include <algorithm>
int k;
int main()
{
	for(scanf("%d", &k); k != 0; k--)
	{
		int n, x, t;
		scanf("%d%d%d", &n, &x, &t);
		long long max = std::min((long long)n - 1, (long long)t / x);
		unsigned long long ans = (0 + max) * (max + 1) / 2;
		ans += (n - (max + 1)) * max;
		printf("%llu\n", ans);
	}
	return 0;
}
