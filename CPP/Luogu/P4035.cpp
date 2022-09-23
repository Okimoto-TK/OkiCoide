#include <cstdio>
#include <algorithm>
const double eps = 1e-9;
int n;
double a[15][15];
bool grt(int x, int y, int c)
{
	for(int i = c; i <= n; i++)
	{
		if(std::abs(std::abs(a[x][i]) - std::abs(a[y][i])) > eps) return std::abs(a[x][i]) > std::abs(a[y][i]);
	}
	return false;
}
double x[15];
void gauss()
{
	int r, c;
	for(r = 1, c = 1; c <= n; r++, c++)
	{
		int max = r;
		for(int i = r + 1; i <= n; i++)
		{
			if(grt(i, max, c))
			{
				max = i;
			}
		}
		if(max != r)
		{
			std::swap(a[r], a[max]);
		}
		if(std::abs(a[r][c]) < eps)
		{
			r--;
			continue;
		}
		for(int i = r + 1; i <= n; i++)
		{
			double v = a[i][c] / a[r][c];
			for(int j = c; j <= n + 1; j++)
			{
				a[i][j] -= a[r][j] * v; 
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
double b[15][15];
int main()
{
	scanf("%d", &n);
	for(int i = 1; i <= n + 1; i++)
	{
		for(int j = 1; j <= n; j++)
		{
			scanf("%lf", &b[i][j]);
		}
	}
	for(int i = 1; i <= n; i++)
	{
		for(int j = 1; j <= n; j++)
		{
			a[i][j] = 2 * (b[i + 1][j] - b[i][j]);
			a[i][n + 1] += b[i + 1][j] * b[i + 1][j] - b[i][j] * b[i][j];
		}
	}
	gauss();
	for(int i = 1; i <= n; i++)
	{
		printf("%.3f ", x[i]);
	}
	return 0;
}
