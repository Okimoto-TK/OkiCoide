#include <cstdio>
#include <algorithm>
double eps = 1e-14;
int n, m, k, q;
double a[205][205];
double rho[205][205];
double rsum[205];
double x[205];
double volt[205];
bool cmp(int c, int x, int y)
{
	for(int i = c; i <= n; i++)
	{
		if(std::abs(std::abs(a[x][c]) - std::abs(a[y][c])) > eps) return std::abs(a[x][c]) > std::abs(a[y][c]);
	}
	return false;
}
void gauss()
{
	int r, c;
	for(r = c = 1; c <= n; r++, c++)
	{
		int max = r;
		for(int i = r + 1; i <= n; i++)
		{
			if(cmp(c, i, max))
			{
				max = i;
			}
		}
		if(max != r)
		{
			std::swap(a[max], a[r]);
		}
		if(std::abs(a[r][c]) < eps)
		{
			r--;
			continue;
		}
		for(int i = r + 1; i <= n; i++)
		{
			if(std::abs(a[i][c]) < eps) continue;
			double k = a[i][c] / a[r][c];
			for(int j = c; j <= n + 1; j++)
			{
				a[i][j] -= k * a[r][j];
			}
			a[i][c] = 0;
		}
	}
	for(int i = r; i <= n; i++)
	{
		if(std::abs(a[i][n + 1]) > eps) return;
	}
	if(n + 1 - r != 0) return;
	for(int i = n; i >= 1; i--)
	{
		for(int j = i + 1; j <= n; j++)
		{
			a[i][n + 1] -= a[i][j] * x[j];
		}
		x[i] = a[i][n + 1] / a[i][i];
	}
}
int main()
{
	scanf("%d%d%d%d", &n, &m, &k, &q);
	for(int i = 1; i <= k; i++)
	{
		int id, u;
		scanf("%d %d", &id, &u);
		volt[id] = u;
	}
	for(int i = 1; i <= m; i++)
	{
		int u, v;
		double r;
		scanf("%d%d%lf", &u, &v, &r);
		rho[u][v] += 1.0 / r;
		rsum[u] += 1.0 / r;
		rho[v][u] += 1.0 / r;
		rsum[v] += 1.0 / r;
	}
	for(int i = 1; i <= n; i++)
	{
		if(volt[i] != 0)
		{
			a[i][i] = 1;
			a[i][n + 1] = volt[i];
		}
		else
		{
			for(int j = 1; j <= n; j++)
			{
				if(rho[i][j] != 0)
				{
					a[i][j] = rho[i][j];
				}
			}
			a[i][i] = -rsum[i];
		}
	}
	gauss();
	for(int i = 1; i <= q; i++)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		printf("%.2lf\n", x[u] - x[v]);
	}
	return 0;
}