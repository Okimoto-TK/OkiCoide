#include <cstdio>
int t;
int main()
{
	for(scanf("%d", &t); t != 0; t--)
	{
		int n, k;
		int r = 0;
		scanf("%d%d", &n, &k);
		for(int i = 1; i < n; i++) scanf("%d%d", &r, &r);
		printf("%s\n", n % k == 0 ? "YES" : "NO");
	}
	return 0;
}
