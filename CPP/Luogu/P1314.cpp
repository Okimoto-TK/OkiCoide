#include <cstdio>
#include <cstring>
#include <algorithm>
int n, m;
long long s;
int w[200005];
long long v[200005];
int L[200005];
int R[200005];
long long sum[200005];
long long cnt[200005];
int main()
{
	scanf("%d%d%lld", &n, &m, &s);
	for(int i = 1; i <= n; i++)
	{
		scanf("%d%lld", &w[i], &v[i]);
	}
	for(int i = 1; i <= m; i++)
	{
		scanf("%d%d", &L[i], &R[i]);
	}
	int l = 0;
	int r = 1000005;
	long long ans = 1000000000000000000ll;
	while(l <= r)
	{
		memset(sum, 0, sizeof(sum));
		memset(cnt, 0, sizeof(cnt));
		int mid = (l + r) >> 1;
		for(int i = 1; i <= n; i++)
		{
			sum[i] = sum[i - 1] + ((w[i] >= mid) ? v[i] : 0);
			cnt[i] = cnt[i - 1] + ((w[i] >= mid) ? 1 : 0);
		}
		long long y = 0;
		for(int i = 1; i <= m; i++)
		{
			y += (cnt[R[i]] - cnt[L[i] - 1]) * (sum[R[i]] - sum[L[i] - 1]);
		}
		if(y > s)
		{
			ans = std::min(ans, y - s);
			l = mid + 1;
		}
		else
		{
			ans = std::min(ans, s - y);
			r = mid - 1;
		}
	}
	printf("%lld", ans);
	return 0;
}
