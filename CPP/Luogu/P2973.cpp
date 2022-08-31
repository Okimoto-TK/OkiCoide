#include <cstdio>
#include <algorithm>
const double eps = 1e-12;
double a[305][305];
double e[305][305];
double d[305];
double x[305];
int n, m, p, q;
double po;
void gauss()
{
	int r, c;
	for(r = c = 1; c <= n; r++, c++)
	{
		int max = r;
		for(int i = r + 1; i <= n; i++)
		{
			if(a[i][c] > a[max][c])
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
			double k = a[i][c] / a[r][c];
			for(int j = c; j <= n + 1; j++)
			{
				a[i][j] -= k * a[r][j];
			}
			a[i][c] = 0;
		}
	}
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
	scanf("%d%d%d%d", &n, &m, &p, &q);
	po = double(p) / double(q);
	for(int i = 1; i <= m; i++)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		if(u == v) continue;
		e[u][v]++;
		e[v][u]++;
		d[u]++;
		d[v]++;
	}
	for(int i = 1; i <= n; i++)
	{
		for(int j = 1; j <= n; j++)
		{
			if(i == j)
			{
				a[i][j] = 1;
			}
			else if(std::abs(e[j][i]) > eps)
			{
				a[i][j] = (po - 1) * e[j][i] / d[j];
			}
		}
		if(i == 1)
		{
			a[i][n + 1] = 1;
		}
	}
	gauss();
	for(int i = 1; i <= n; i++)
	{
		printf("%.12lf\n", x[i] * po);
	}
	return 0;
}