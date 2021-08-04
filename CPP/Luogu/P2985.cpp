#include <cstdio>
int n, d;
long long h[50005];
int ans[50005];
bool check(long long x)
{
	int ptr = 1;
	long long hpy = 0;
	for(int i = 1; i <= d; i++)
	{
		while(ptr <= n && hpy < x)
		{
			hpy += h[ptr];
			ans[ptr++] = i;
		}
		if(ptr > n && hpy < x) return false;
		hpy /= 2;
	}
	for(; ptr <= n; ptr++) ans[ptr] = d;
	return true;
}
int main()
{
	scanf("%d%d", &n, &d);
	long long l = 0;
	long long r = 0;
	for(int i = 1; i <= n; i++)
	{
		scanf("%lld", &h[i]);
		r += h[i];
	}
	while(l < r)
	{
		long long mid = (l + r + 1) >> 1;
		if(check(mid)) l = mid;
		else r = mid - 1;
	}
	check(l);
	printf("%lld\n", l);
	for(int i = 1; i <= n; i++) printf("%d\n", ans[i]);
	return 0;
}
