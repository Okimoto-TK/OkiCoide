#include <cstdio>
#include <vector>
#define N 100000
int n, q;
double ans = 0;
double p[N + 5];
double _psum[N + 5];
int fa[N + 5];
std::vector<int> vec[N + 5];
void dfs(int u, int f)
{
	fa[u] = f;
	ans += p[f] * (1 - p[u]);
	for(auto v : vec[u])
	{
		if(v == f) continue;
		dfs(v, u);
		_psum[u] += (1 - p[v]);
	}
}
int main()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
	{
		scanf("%lf", &p[i]);
	}
	for(int i = 1; i < n; i++)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		u++, v++;
		vec[u].push_back(v);
		vec[v].push_back(u);
	}
	p[0] = 1;
	dfs(1, 0);
	scanf("%d", &q);
	for(int i = 1; i <= q; i++)
	{
		int x;
		double v;
		scanf("%d%lf", &x, &v);
		x++;
		ans -= p[fa[x]] * (1 - p[x]);
		ans -= p[x] * _psum[x];
		_psum[fa[x]] -= (1 - p[x]);
		p[x] = v;
		ans += p[fa[x]] * (1 - p[x]);
		ans += p[x] * _psum[x];
		_psum[fa[x]] += (1 - p[x]);
		printf("%.6f\n", ans);
	}
	return 0;
}