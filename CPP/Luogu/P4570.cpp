#include <cstdio>
#include <algorithm>
struct item
{
	long long num;
	int mag;
} a[1005];
struct Bas
{
	long long bas[65];
	bool insert(long long x)
	{
		for(int d = 63; d >= 0; d--)
		{
			if(x & (1ll << d))
			{
				if(bas[d] == 0)
				{
					bas[d] = x;
					return true;
				}
				else
				{
					x ^= bas[d];
				}
			}
		}
		return false;
	}
} b;
bool cmp(item x, item y)
{
	return x.mag > y.mag;
}
int n;
int main()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
	{
		scanf("%lld%d", &a[i].num, &a[i].mag);
	}
	std::sort(a + 1, a + 1 + n, cmp);
	int ans = 0;
	for(int i = 1; i <= n; i++)
	{
		if(b.insert(a[i].num))
		{
			ans += a[i].mag;
		}
	}
	printf("%d", ans);
	return 0;
}