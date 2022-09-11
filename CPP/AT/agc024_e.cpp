#include <cstdio>
int n, k, mod;
long long f[305][305];
long long g[305][305];
long long c[305][305];
void comb()
{
	c[0][0] = 1;
	for(int i = 1; i <= 300; i++)
	{
		c[i][0] = c[i][i] = 1;
		for(int j = 1; j < i; j++)
		{
			c[i][j] = (c[i - 1][j - 1] + c[i - 1][j]) % mod;
		}
	}
}
int main()
{
	scanf("%d%d%d", &n, &k, &mod);
	comb();
	for(int i = k; i >= 0; i--)
	{
		f[1][i] = 1;
		g[1][i] = g[1][i + 1] + f[1][i];
	}
	for(int i = 2; i <= n + 1; i++)
	{
		for(int j = 0; j <= k; j++)
		{
			for(int l = 1; l <= i - 1; l++)
			{
				(f[i][j] += f[i - l][j] * c[i - 2][l - 1] % mod * g[l][j + 1] % mod) %= mod;
			}
		}
		g[i][k] = f[i][k];
		for(int j = k - 1; j >= 0; j--)
		{
			g[i][j] = (g[i][j + 1] + f[i][j]) % mod;
		}
	}
	printf("%lld", f[n + 1][0]);
	return 0;
}