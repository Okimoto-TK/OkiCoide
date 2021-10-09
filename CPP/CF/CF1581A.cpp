#include <cstdio>
int t;
int main()
{
	for(scanf("%d", &t); t != 0; t--)
	{
		int n;
		scanf("%d", &n);
		long long ans = 1;
		for(int i = 3; i <= 2 * n; i++) (ans *= i % 1000000007) %= 1000000007;
		printf("%lld\n", ans);
	}
}
