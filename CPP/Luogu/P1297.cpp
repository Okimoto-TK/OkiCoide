#include <cstdio>
#include <algorithm>
#define P 100000001
int n, A, B, C;
int a[10000005];
int main()
{
	scanf("%d%d%d%d%d", &n, &A, &B, &C, &a[1]);
	for(int i = 2; i <= n; i++) a[i] = (1ll * a[i - 1] * A + B) % P;
	for(int i = 1; i <= n; i++) (a[i] %= C) += 1;
	double ans = 0;
	for(int i = 1; i <= n; i++)
	{
		int j = i + 1 > n ? 1 : i + 1;
		ans += 1.0 / double(std::max(a[i], a[j]));
	}
	printf("%.3lf", ans);
	return 0;
}
