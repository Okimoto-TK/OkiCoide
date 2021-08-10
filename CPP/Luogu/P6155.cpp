#include <cstdio>
#include <algorithm>
#include <map>
int n;
int a[1000005];
int b[1000005];
int c[1000005];
std::map<int, int> link;
int find(int x)
{
	if(link[x] == 0) return x;
	return link[x] = find(link[x]);
}
bool cmp(int x, int y)
{
	return x > y;
}
bool cmp2(int x, int y)
{
	return x < y;
}
int main()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
	{
		scanf("%d", &a[i]);
	}
	std::sort(a + 1, a + 1 + n, cmp);
	for(int i = 1; i <= n; i++)
	{
		if(link[a[i]] == 0)
		{
			c[i] = 0;
			link[a[i]] = find(a[i] + 1);
		}
		else
		{
			int pos = find(link[a[i]]);
			c[i] = pos - a[i];
			link[pos] = find(pos + 1);
		}
	}
	std::sort(c + 1, c + 1 + n, cmp);
	for(int i = 1; i <= n; i++)
	{
		scanf("%d", &b[i]);
	}
	std::sort(b + 1, b + 1 + n, cmp2);
	unsigned long long ans = 0;
	for(int i = 1; i <= n; i++)
	{
		ans += (unsigned long long)b[i] * c[i];
	}
	printf("%llu", ans);
	return 0;
}
