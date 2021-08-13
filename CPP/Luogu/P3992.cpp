#include <cstdio>
#include <vector>
#include <algorithm>
int n, q;
int v[50005];
std::vector<int> a;
std::vector<int> b;
int main()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
	{
		int _a;
		scanf("%d", &_a);
		v[i] = _a;
		a.push_back(_a);
	}
	for(int i = 1; i <= n; i++)
	{
		int _b;
		scanf("%d", &_b);
		b.push_back(_b);
	}
	std::sort(a.begin(), a.end());
	std::sort(b.begin(), b.end());
	long long ans = 0;
	for(int i = 0; i < n; i++)
	{
		ans += std::abs(a[i] - b[i]);
	}
	printf("%lld\n", ans);
	scanf("%d", &q);
	for(int i = 1; i <= q; i++)
	{
		int u, w;
		scanf("%d%d", &u, &w);
		a.erase(std::lower_bound(a.begin(), a.end(), v[u]));
		v[u] = w;
		a.insert(std::lower_bound(a.begin(), a.end(), v[u]), v[u]);
		long long ans = 0;
		for(int j = 0; j < n; j++)
		{
			ans += std::abs(a[j] - b[j]);
		}
		printf("%lld\n", ans);
	}
	return 0;
}
