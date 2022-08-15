#include <cstdio>
#include <algorithm>
#define int long long
struct node
{
	int s, p;
} a[100005], c[100005];
int n, b, bp;
int min[100005];
int mn[100005];
bool cmp(node x, node y)
{
	return x.p < y.p;
}
bool cmp1(node x, node y)
{
	return x.p > y.p;
}
int half1(int l, int r, int x)
{
	int _l = l;
	while(l < r)
	{
		int mid = (l + r + 1) >> 1;
		if(mid == _l)
		{
			l = mid;
		}
		else if(std::abs(a[mid].p - b) <= x)
		{
			l = mid;
		}
		else
		{
			r = mid - 1;
		}
	}
	return _l == l ? -1 : l;
}
int half2(int l, int r, int x)
{
	int _l = l;
	while(l < r)
	{
		int mid = (l + r + 1) >> 1;
		if(mid == _l)
		{
			l = mid;
		}
		else if(std::abs(c[mid].p - b) <= x)
		{
			l = mid;
		}
		else
		{
			r = mid - 1;
		}
	}
	return _l == l ? -1 : l;
}
signed main()
{
	//freopen("in.in", "r", stdin);
	scanf("%lld%lld", &n, &b);
	for(int i = 1; i <= n; i++)
	{
		scanf("%lld%lld", &a[i].s, &a[i].p);
		c[i].s = a[i].s;
		c[i].p = a[i].p;
	}
	std::sort(a + 1, a + 1 + n, cmp);
	std::sort(c + 1, c + 1 + n, cmp);
	for(int i = 1; i <= n; i++)
	{
		if(b > a[i].p) bp = i;
	}
	std::sort(c + 1, c + 1 + bp, cmp1);
	if(bp == 0 || bp == n)
	{
		printf("-1");
		return 0;
	}
	min[bp] = b - a[bp].p - a[bp].s;
	//printf("%lld\n", min[78205]);
	mn[bp] = bp;
	for(int i = bp - 1; i >= 1; i--)
	{
		min[i] = std::min(min[i + 1], b - a[i].p - a[i].s);
		if(min[i] < min[i + 1]) mn[i] = i;
		else mn[i] = mn[i + 1];
	}
	min[bp + 1] = a[bp + 1].p - b - a[bp + 1].s;
	mn[bp + 1] = bp + 1;
	for(int i = bp + 2; i <= n; i++)
	{
		min[i] = std::min(min[i - 1], a[i].p - b - a[i].s);
		if(min[i] < min[i - 1]) mn[i] = i;
		else mn[i] = mn[i - 1];
	}
	//for(int i = 1; i <= n; i++) printf("%d ", min[i]);
	//printf("\n");
	int ans = 0x3f3f3f3f3f3f3f3f;
	int ans1, ans2;
	//printf("%lld %lld\n", a[78205].s - std::abs(b - a[78205].p), std::abs(a[99580].p - b));
	for(int i = 1; i <= bp; i++)
	{
		//if(i == 78205) printf("%lld\n", std::abs(b - a[i].p) - a[i].s);
		if(std::abs(b - a[i].p) - a[i].s < 0)
		{
			int r = half1(bp, n, a[i].s - std::abs(b - a[i].p));
			//if(i == 78205) printf("%lld\n", r);
			//printf("%d %d %d\n", i, r, a[i].s - std::abs(b - a[i].p));
			if(r == -1) continue;
			if(std::abs(b - a[i].p) + min[r] < ans)
			{
				ans1 = i, ans2 = mn[r];
				//printf("1\n");
			}
			ans = std::min(ans, std::abs(b - a[i].p) + min[r]);
		}
	}
	for(int i = bp + 1; i <= n; i++)
	{
		//if(i == 99580) printf("%lld\n", std::abs(b - a[i].p) - a[i].s);
		//if(i == 99580) printf("%lld\n", std::abs(b - a[78205].p));
		if(std::abs(b - a[i].p) - a[i].s < 0)
		{
			int r = half2(0, bp, a[i].s - std::abs(b - a[i].p));
			//if(i == 99580) printf("%lld ", std::abs(b - a[78205].p));
			//if(i == 99580) printf("%lld\n", r);
			//printf("%d %d\n", i, r);
			if(r == -1) continue;
			if(std::abs(b - a[i].p) + min[r] < ans)
			{
				ans2 = i, ans1 = mn[r];
				//printf("2\n");
			}
			ans = std::min(ans, std::abs(b - a[i].p) + min[bp + 1 - r]);
		}
	}
	//printf("%lld %lld\n", ans1, ans2);
	if(ans == 0x3f3f3f3f3f3f3f3f)
	{
		printf("-1");
		return 0;
	}
	printf("%lld", std::max(ans, 0ll));
	return 0;
}