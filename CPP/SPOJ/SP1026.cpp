#include <cstdio>
int T;
int main()
{
	for(scanf("%d", &T); T != 0; T--)
	{
		int n;
		scanf("%d", &n);
		double ans = 0;
		for(int i = n; i >= 1; i--) ans += double(n) / double(i);
		printf("%.2lf\n", ans);
	}
}
