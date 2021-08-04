#include <cstdio>
#include <algorithm>
int n;
long long k;
long long x[100005];
long long check(long long v)
{
	int cnt = 0;
	long long buf = 0;
	for(int i = 1; i <= n; i++)
	{
		buf = std::max(0ll, buf + x[i]);
		if(buf >= v) buf = 0, cnt++;
	}
	return cnt;
}
int main()
{
	scanf("%d%lld", &n, &k);
	for(int i = 1; i <= n; i++)
	{
		scanf("%lld", &x[i]);
	}
	// min
	long long l = 1;
	long long r = 1e14, min, max;
	bool ans = false;
	while(l <= r)
	{
		long long mid = (l + r) >> 1;
		if(check(mid) >= k)
		{
			if(check(mid) == k) ans = true;
			l = mid + 1;
			max = mid;
		}
		else
		{
			r = mid - 1;
		}
	}
	l = 1;
	r = 1e14;
	while(l <= r)
	{
		long long mid = (l + r) >> 1;
		if(check(mid) <= k)
		{
			r = mid - 1;
			min = mid;
		}
		else
		{
			l = mid + 1;
		}
	}
	if(!ans) printf("-1");
	else printf("%lld %lld", min, max);
	return 0;
}
