#include <cstdio>
#include <algorithm>
int n;
double a[1000005];
int main()
{
	//freopen("in.in", "r", stdin);
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
	{
		scanf("%lf", &a[i]);
	}
	std::sort(a + 1, a + 1 + n);
	double sum = 0;
	int ans = 0;
	for(int i = 1; i <= n; i++)
	{
		sum += a[i];
		int val = (a + 1 + i) - std::upper_bound(a + 1, a + 1 + i, sum / i);
		ans = std::max(ans, val);
	}
	printf("%d", ans);
	return 0;
}