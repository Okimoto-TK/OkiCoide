#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
const int mod = 1e9 + 7;
long long power(long long x, int k)
{
	long long r = 1;
	while(k)
	{
		if(k&1)
		{
			(r *= x) %= mod;
		}
		(x *= x) %= mod;
		k >>= 1;
	}
	return r;
}
int n;
std::vector<int> g[205];
int dep[205];
int f[205][10];
long long h[205][205];
void dfs(int u, int fa)
{
	dep[u] = dep[fa] + 1;
	for(int b = 0; b <= 8; b++)
	{
		f[u][b + 1] = f[f[u][b]][b];
	}
	for(auto v : g[u])
	{
		if(v != fa)
		{
			f[v][0] = u;
			dfs(v, u);
		}
	}
}
int lca(int x, int y)
{
	if(dep[x] < dep[y])
	{
		std::swap(x, y);
	}
	for(int b = 9; b >= 0; b--)
	{
		if(dep[x] - (1 << b) >= dep[y])
		{
			x = f[x][b];
		}
	}
	if(x == y) return x;
	for(int b = 9; b >= 0; b--)
	{
		if(f[x][b] != f[y][b])
		{
			x = f[x][b];
			y = f[y][b];
		}
	}
	return f[x][0];
}
int main()
{
	scanf("%d", &n);
	for(int i = 1; i < n; i++)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		g[u].push_back(v);
		g[v].push_back(u);
	}
	for(int i = 1; i <= n; i++)
	{
		h[0][i] = 1;
	}
	for(int u = 1; u <= n; u++)
	{
		for(int v = 1; v <= n; v++)
		{
			h[u][v] = (h[u - 1][v] + h[u][v - 1]) * power(2, mod - 2) % mod;
		}
	}
	long long cnt = 0;
	for(int root = 1; root <= n; root++)
	{
		memset(f, 0, sizeof(f));
		dfs(root, 0);
		for(int u = 1; u <= n; u++)
		{
			for(int v = 1; v < u; v++)
			{
				int c = lca(u, v);
				(cnt += h[dep[u] - dep[c]][dep[v] - dep[c]]) %= mod;
			}
		}
	}
	(cnt *= power(n, mod - 2)) %= mod;
	printf("%lld", (cnt + mod) % mod);
	return 0;
}