#include <cstdio>
#include <cmath>
#include <algorithm>
int n;
double matrix[105][105];
double x[105];
int main()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
	{
		for(int j = 1; j <= n + 1; j++)
		{
			scanf("%lf", &matrix[i][j]);
		}
	}
	for(int i = 1; i <= n; i++)
	{
		double max = -(0x3f3f3f3f);
		int ptr = -1;
		for(int j = i; j <= n; j++)
		{
			if(max < matrix[j][i])
			{
				max = matrix[j][i];
				ptr = j;
			}
		}
		for(int j = 1; j <= n + 1; j++)
		{
			std::swap(matrix[ptr][j], matrix[i][j]);
		}
		for(int j = 1; j <= n; j++)
		{
			if(i == j) continue;
			double r = matrix[j][i] / matrix[i][i];
			for(int k = 1; k <= n + 1; k++)
			{
				matrix[j][k] -= matrix[i][k] * r;
			}
		}
	}
	for(int i = n; i >= 1; i--)
	{
		double ans = matrix[i][n + 1];
		for(int j = n; j > i; j--)
		{
			ans -= matrix[i][j] * x[j];
		}
		if(fabs(matrix[i][i]) <= 0.00000001)
		{
			printf("No Solution");
			return 0;
		}
		x[i] = ans / matrix[i][i];
	}
	for(int i = 1; i <= n; i++) printf("%.2lf\n", x[i]);
	return 0;
}
