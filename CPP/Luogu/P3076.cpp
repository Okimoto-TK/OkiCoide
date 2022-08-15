#include <cstdio>
#include <algorithm>
int n, m;
int s[100005];
int t[100005];
long long ans;
int main()
{
	scanf("%d%d", &n, &m);
	s[0] = m;
	t[0] = 0;
	for(int i = 1; i <= n; i++)
	{
		scanf("%d%d", &s[i], &t[i]);
		ans += 1ll * std::abs(s[i] - t[i]);
	}
	std::sort(s, s + 1 + n);
	std::sort(t, t + 1 + n);
	for(int i = 0; i <= n; i++)
	{
		ans += 1ll * std::abs(s[i] - t[i]);
	}
	printf("%lld", ans);
	return 0;
}