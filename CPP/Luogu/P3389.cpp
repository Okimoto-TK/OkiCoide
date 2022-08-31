#include <cstdio>
#include <algorithm>
#define N 100
const double eps = 1e-8;
int n;
double a[N + 5][N + 5];
double x[N + 5];
bool grt(int r, int x, int y)
{
	if(a[x][r] != a[y][r]) return a[x][r] > a[y][r];
	for(int i = r + 1; i < n; i++)
	{
		if(a[x][i] != a[y][i]) return a[x][i] > a[y][i];
	}
	return false;
}
int gauss()
{
	int r, c;
	for(r = 0, c = 0; r < n && c < n; r++, c++)
	{
		int max = r;
		for(int j = r + 1; j < n; j++)
		{
			if(grt(c, j, max))
			{
				max = j;
			}
		}
		if(max != r) std::swap(a[r], a[max]);
		if(std::abs(a[r][c]) < eps)
		{
			r--;
			continue;
		}
		for(int j = r + 1; j < n; j++)
		{
			if(std::abs(a[j][c]) < eps) continue;
			double v = a[j][c] / a[r][c];
			for(int k = c; k <= n; k++)
			{
				a[j][k] -= a[r][k] * v;
			}
			a[j][c] = 0;
		}
	}
	for(int i = r; i < n; i++)
	{
		if(std::abs(a[i][n]) >= eps) return -1;
	}
	if(r < n) return n - r;
	for(int i = n - 1; i >= 0; i--)
	{
		for(int j = i + 1; j < n; j++)
		{
			a[i][n] -= a[i][j] * x[j];
		}
		x[i] = a[i][n] / a[i][i];
	}
	return 0;
}
int main()
{
	scanf("%d", &n);
	for(int i = 0; i < n; i++)
	{
		for(int j = 0; j <= n; j++)
		{
			scanf("%lf", &a[i][j]);
		}
	}
	if(gauss() != 0)
	{
		printf("No Solution");
	}
	else
	{
		for(int i = 0; i < n; i++)
		{
			printf("%.2lf\n", x[i]);
		}
	}
	return 0;
}