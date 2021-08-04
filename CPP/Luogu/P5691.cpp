#include <cstdio>
#include <map>
int n, m;
int k[10];
int p[10];
std::map<long long, int> cnt;
long long power(long long x, int k)
{
	long long r = 1;
	while(k != 0)
	{
		if(k & 1) r *= x;
		x *= x;
		k >>= 1;
	}
	return r;
}
void dfs1(int dep, long long x)
{
	if(dep == n / 2)
	{
		cnt[x]++;
		return;
	}
	for(int i = 1; i <= m; i++) dfs1(dep + 1, x + k[dep + 1] * power(i, p[dep + 1]));
}
long long ans;
void dfs2(int dep, long long x)
{
	if(dep == n - n / 2)
	{
		ans += cnt[-x];
		return;
	}
	for(int i = 1; i <= m; i++) dfs2(dep + 1, x + k[dep + 1 + n / 2] * power(i, p[dep + 1 + n / 2]));
}
int main()
{
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++) scanf("%d%d", &k[i], &p[i]);
	dfs1(0, 0ll);
	dfs2(0, 0ll);
	printf("%lld", ans);
	return 0;
}
