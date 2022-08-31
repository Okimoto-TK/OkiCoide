#include <cstdio>
#include <algorithm>
#define N 50
const double eps = 1e-6;
int n;
double a[N + 5][N + 5];
double x[N + 5];
bool grt(int c, int x, int y)
{
	for(int i = c; i <= n; i++)
	{
		if(std::abs(std::abs(a[x][i]) - std::abs(a[y][i])) > eps) return std::abs(a[x][i]) > std::abs(a[y][i]);
	}
	return false;
}
int gauss()
{
	int r, c;
	for(r = 1, c = 1; r <= n && c <= n; r++, c++)
	{
		int max = r;
		for(int i = r + 1; i <= n; i++)
		{
			if(grt(c, i, max))
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
			double v = a[i][c] / a[r][c];
			for(int j = c; j <= n + 1; j++)
			{
				a[i][j] -= a[r][j] * v;
			}
			a[i][c] = 0;
		}
	}
	for(int i = r; i <= n; i++)
	{
		if(std::abs(a[i][n + 1]) >= eps) return -1;
	}
	if(n + 1 - r != 0) return n + 1 - r;
	for(int i = n; i >= 1; i--)
	{
		for(int j = i + 1; j <= n; j++)
		{
			a[i][n + 1] -= x[j] * a[i][j];
		}
		x[i] = a[i][n + 1] / a[i][i];
	}
	return 0;
}
int main()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
	{
		for(int j = 1; j <= n + 1; j++)
		{
			scanf("%lf", &a[i][j]);
		}
	}
	int r = gauss();
	if(r == -1)
	{
		printf("-1");
	}
	else if(r > 0)
	{
		printf("0");
	}
	else
	{
		for(int i = 1; i <= n; i++)
		{
			printf("x%d=%.2lf\n", i, x[i]);
		}
	}
	return 0;
}