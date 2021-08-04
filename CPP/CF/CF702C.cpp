#include <cstdio>
#include <cstdlib>
#include <algorithm>
int n, m;
int a[100005];
int b[100005];
int d[100005];
void init()
{
	for(int i = 1; i <= n; i++)
	{
		d[i] = std::lower_bound(b + 1, b + 1 + m, a[i]) - b;
	}
}
bool check(int r)
{
	for(int i = 1; i <= n; i++)
	{
		int x = d[i];
		if(x == m + 1)
		{
			if(abs(a[i] - b[m]) > r) return false;
		}
		else if(x == 1)
		{
			if(abs(a[i] - b[1]) > r) return false;
		}
		else
		{
			if(abs(a[i] - b[x]) > r && abs(a[i] - b[x - 1]) > r) return false;
		}
	}
	return true;
}
int main()
{
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++)
	{
		scanf("%d", &a[i]);
	}
	for(int i = 1; i <= m; i++)
	{
		scanf("%d", &b[i]);
	}
	init();
	long long l = 0;
	long long r = 2000000005;
	while(l < r)
	{
		long long mid = (l + r) >> 1;
		if(check(mid)) r = mid;
		else l = mid + 1;
	}
	printf("%lld", l);
	return 0;
}
