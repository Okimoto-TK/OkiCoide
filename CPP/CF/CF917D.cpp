#include <cstdio> 
#include <cstring>
#include <vector>
#define N 100
const int mod = 1e9 + 7;
int n;
int siz[N + 5];
long long f[N + 5][N + 5][2];
long long g[N + 5][2];
long long a[N + 5];
std::vector<int> vec[N + 5];
void dfs(int u, int fa)
{
	f[u][1][0] = 1;
	f[u][1][1] = 1;
	siz[u] = 1;
	for(auto v : vec[u])
	{
		if(v == fa) continue;
		dfs(v, u);
		for(int i = 1; i <= siz[u]; i++)
		{
			for(int j = 1; j <= siz[v]; j++)
			{
				(g[i + j][0] += f[u][i][0] * f[v][j][1]) %= mod;
				(g[i + j][1] += f[u][i][1] * f[v][j][1]) %= mod;
				(g[i + j - 1][0] += f[u][i][0] * f[v][j][0]) %= mod;
				(g[i + j - 1][1] += f[u][i][1] * f[v][j][0]) %= mod;
				(g[i + j - 1][1] += f[u][i][0] * f[v][j][1]) %= mod;
			}
		}
		siz[u] += siz[v];
		for(int i = 1; i <= siz[u]; i++)
		{
			f[u][i][0] = g[i][0];
			f[u][i][1] = g[i][1];
			g[i][0] = g[i][1] = 0;
		}
	}
}
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
int c[N + 5][N + 5];
void init()
{
	c[0][0] = 1;
	for(int i = 1; i <= n; i++)
	{
		c[i][0] = 1;
		c[i][i] = 1;
		for(int j = 1; j < i; j++)
		{
			c[i][j] = (c[i - 1][j] + c[i - 1][j - 1]) % mod;
		}
	}
}
int main()
{
	memset(f, -1, sizeof(f));
	scanf("%d", &n);
	for(int i = 1; i < n; i++)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		vec[u].push_back(v);
		vec[v].push_back(u);
	}
	dfs(1, 0);
	for(int k = 0; k < n - 1; k++)
	{
		int b = n - k;
		a[k] = power(n, (b - 2 + mod - 1) % (mod - 1)) * f[1][b][1] % mod;
	}
	a[n - 1] = 1;
	init();
	for(int i = 0; i < n; i++)
	{
		long long ans = 0;
		for(int x = i; x < n; x++)
		{
			(ans += 1ll * (((i - x) % 2 == 0) ? 1 : -1) * c[x][i] * a[x] % mod) %= mod;
		}
		printf("%lld\n", (ans + mod) % mod);
	}
	return 0;	
}
