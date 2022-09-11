#include <cstdio>
#include <vector>
#define N 1000000
const int mod = 998244353;
int n, q;
int lca[N][22];
int dep[N];
long long f[N + 5];
long long g[N + 5];
std::vector<int> vec[N + 5];
void dfs0(int u, int fa)
{
	dep[u] = dep[fa] + 1;
	lca[u][0] = fa;
	for(int i = 1; (1 << i) <= dep[u]; i++)
	{
		lca[u][i] = lca[lca[u][i - 1]][i - 1];
	}
	for(auto v : vec[u])
	{
		if(v == fa) continue;
		dfs0(v, u);
	}
}
void dfs1(int u, int fa)
{
	for(auto v : vec[u])
	{
		if(v == fa) continue;
		dfs1(v, u);
		(f[u] += 2 * f[v]) %= mod;
	}
	f[u]++;
}
void dfs2(int u, int fa)
{
	for(auto v : vec[u])
	{
		if(v == fa) continue;
		(g[v] = f[u] - 2 * f[v] + 2 * g[u]) %= mod;
		dfs2(v, u);
	}
}
int Lca(int x, int y)
{
	if(dep[x] < dep[y])
	{
		std::swap(x, y);
	}
	for(int i = 20; i >= 0; i--)
	{
		if(dep[lca[x][i]] > dep[y])
		{
			x = lca[x][i];
		}
	}
	if(lca[x][0] == y) return x;
	if(dep[x] > dep[y]) x = lca[x][0];
	for(int i = 20; i >= 0; i--)
	{
		if(lca[x][i] != lca[y][i])
		{
			x = lca[x][i];
			y = lca[y][i];
		}
	}
	return lca[x][0];
}
long long power(long long x, int k)
{
	long long r = 1;
	while(k)
	{
		if(k & 1)
		{
			(r *= x) %= mod;
		}
		(x *= x) %= mod;
		k >>= 1;
	}
	return r;
}
int main()
{
	scanf("%d", &n);
	for(int i = 1; i < n; i++)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		vec[u].push_back(v);
		vec[v].push_back(u);
	}
	dfs0(1, 0);
	dfs1(1, 0);
	dfs2(1, 0);
	scanf("%d", &q);
	for(int i = 1; i <= q; i++)
	{
		int x, y;
		scanf("%d%d", &x, &y);
		if(dep[x] < dep[y])
		{
			std::swap(x, y);
		}
		int c = Lca(x, y);
		long long ans = 1;
		if(lca[c][0] == y)
		{
			(ans *= f[x]) %= mod;
			(ans *= g[c]) %= mod;
			(ans *= power(2, dep[x] - dep[y])) %= mod;
		}
		else
		{
			(ans *= f[x]) %= mod;
			(ans *= f[y]) %= mod;
			(ans *= power(2, dep[x] - dep[c] + dep[y] - dep[c])) %= mod;
		}
		printf("%lld\n", (ans % mod + mod) % mod);
	}
	return 0;
}