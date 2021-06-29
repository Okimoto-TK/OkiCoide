#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#define N 2004
int n, m, v, e;
int c[N];
int d[N];
long double p[N];
long double a[N][N];
long double f[N][N][2];
long double g[N][N][2];
long double ans = 1e10;
int main()
{
	// freopen("P1850_16.in", "r", stdin);
	// freopen("P1850_16.ans", "w", stdout);
	for(int i = 0; i < N; i++)
	{
		for(int j = 0; j < N; j++) a[i][j] = f[i][j][0] = f[i][j][1] = g[i][j][0] = g[i][j][1] = 1e11;
	}
	scanf("%d%d%d%d", &n, &m, &v, &e);
	for(int i = 1; i <= n; i++) scanf("%d", &c[i]);
	for(int i = 1; i <= n; i++) scanf("%d", &d[i]);
	for(int i = 1; i <= n; i++) scanf("%Lf", &p[i]);
	for(int i = 1; i <= v; i++) a[i][i] = 0;
	for(int i = 1; i <= e; i++)
	{
		int u, _v;
		double w;
		scanf("%d%d%lf", &u, &_v, &w);
		a[u][_v] = std::min(a[u][_v], (long double)w);
		a[_v][u] = std::min(a[_v][u], (long double)w);
	}
	for(int k = 1; k <= v; k++)
	{
		for(int i = 1; i <= v; i++)
		{
			for(int j = 1; j < i; j++)
			{
				if(a[i][j] > a[i][k] + a[k][j]) a[j][i] = a[i][j] = a[i][k] + a[k][j];
			}
		}
	}
	f[m][1][0] = 0;
	f[m - 1][1][1] = 0;
	g[m - 1][1][0] = p[1] * a[d[1]][c[2]] + (1 - p[1]) * a[c[1]][c[2]];
	g[m - 1][1][1] = p[1] * a[d[1]][d[2]] + (1 - p[1]) * a[c[1]][d[2]];
	for(int i = 2; i <= n; i++)
	{
		for(int j = 0; j <= m; j++)
		{
			f[j][i][0] = std::min(f[j][i - 1][0] + a[c[i - 1]][c[i]], f[j][i - 1][1] + g[j][i - 1][0]);
			if(j != m)
			{
				f[j][i][1] = std::min(f[j + 1][i - 1][0] + p[i] * a[c[i - 1]][d[i]] + (1 - p[i]) * a[c[i - 1]][c[i]], f[j + 1][i - 1][1] + p[i] * g[j + 1][i - 1][1] + (1 - p[i]) * g[j + 1][i - 1][0]);
				if(i != n)
				{
					g[j][i][0] = p[i] * a[d[i]][c[i + 1]] + (1 - p[i]) * a[c[i]][c[i + 1]];
					g[j][i][1] = p[i] * a[d[i]][d[i + 1]] + (1 - p[i]) * a[c[i]][d[i + 1]];
				}
			}
		}
	}
	for(int i = 0; i <= m; i++)
	{
		ans = std::min(ans, std::min(f[i][n][0], f[i][n][1]));
	}
	printf("%.2Lf", ans);
	return 0;
}
