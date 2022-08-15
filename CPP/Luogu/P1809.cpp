#include <cstdio>
#include <cstring>
#include <algorithm>
int t, n;
int a[100005];
int main()
{
	//for(scanf("%d", &t); t; t--)
//	{
		scanf("%d", &n);
		for(int i = 1; i <= n; i++)
		{
			scanf("%d", &a[i]);
		}
		std::sort(a + 1, a + 1 + n);
		int ptr;
		long long ans = 0;
		for(ptr = n; ptr > 3; ptr -= 2)
		{
			ans += std::min(2 * a[2] + a[1] + a[ptr], 2 * a[1] + a[ptr - 1] + a[ptr]);
		}
		if(ptr == 3)
		{
			ans += a[3] + a[1] + a[2];
		}
		else if(ptr == 2)
		{
			ans += a[2];
		}
		else if(ptr == 1)
		{
			ans += a[1];
		}
		printf("%lld\n", ans);
//	}
	return 0;
}