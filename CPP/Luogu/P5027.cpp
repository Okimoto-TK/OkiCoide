#include <cstdio>
#include <cstring>
#include <algorithm>
double eps = 1e-6;
int n;
int a[105][105];
double ma[105][105];
double x[105];
bool cmp(int c, int x, int y)
{
	for(int i = c; i <= n; i++)
	{
		if(std::abs(std::abs(ma[x][i]) - std::abs(ma[y][i])) > eps) return std::abs(ma[x][i]) > std::abs(ma[y][i]);
	}
	return false;
}
bool isInt(double x)
{
	return std::abs(x - (int)x) < eps;
}
int gauss()
{
	int r = 1, c = 1;
	for(; c <= n; r++, c++)
	{
		int max = r;
		for(int i = r + 1; i <= n; i++)
		{
			if(cmp(c, i, max))
			{
				max = i;
			}
		}
		if(max != r) std::swap(ma[max], ma[r]);
		if(std::abs(ma[r][c]) < eps)
		{
			r--;
			continue;
		}
		for(int i = r + 1; i <= n; i++)
		{
			if(std::abs(ma[i][c]) < eps) continue;
			double k = ma[i][c] / ma[r][c];
			for(int j = c; j <= n + 1; j++)
			{
				ma[i][j] -= k * ma[r][j];
			}
			ma[i][c] = 0;
		}
	}
	/*
	printf("%d\n", c);
	for(int i = 1; i <= n; i++)
	{
		for(int j = 1; j <= n + 1; j++)
		{
			printf("%.2lf ", ma[i][j]);
		}
		putchar('\n');
	}
	*/
	for(int i = r; i <= n; i++)
	{
		if(ma[i][n + 1] > eps) return -1;
	}
	if(n + 1 - r != 0) return n + 1 - r;
	for(int i = n; i >= 1; i--)
	{
		for(int j = i + 1; j <= n; j++)
		{
			ma[i][n + 1] -= ma[i][j] * x[j];
		}
		x[i] = ma[i][n + 1] / ma[i][i];
	}
	return 0;
}
void copy()
{
	memset(ma, 0, sizeof(ma));
	for(int i = 1; i <= n; i++)
	{
		for(int j = 1; j <= n + 1; j++)
		{
			ma[i][j] = a[i][j];
		}
	}
}
int main()
{
	scanf("%d", &n);
	for(int i = 1; i <= n + 1; i++)
	{
		int m;
		scanf("%d", &m);
		for(int j = 1; j <= m; j++)
		{
			int x;
			scanf("%d", &x);
			a[i][x]++;
		}
		scanf("%d", &a[i][n + 1]);
	}
	int ans = -1;
	for(int i = 1; i <= n + 1; i++)
	{
		if(i <= n)
		{
			std::swap(a[i], a[n + 1]);
		}
		else
		{
			std::swap(a[1], a[n + 1]);
		}
		copy();
		int g = gauss();
		if(g != 0) continue;
		int max = -1;
		int maxi;
		/*
		for(int i = 1; i <= n; i++)
		{
			printf("%.2lf ", x[i]);
		}
		*/
		//putchar('\n');
		for(int i = 1; i <= n; i++)
		{
			if(!isInt(x[i]) || (int)x[i] <= 0)
			{
				max = -1;
				break;
			}
			else
			{
				if(max < (int)x[i])
				{
					max = (int)x[i];
					maxi = i;
 				}
			}
		}
		if(max == -1) continue;
		int cnt = 0;
		for(int i = 1; i <= n; i++)
		{
			if((int)x[i] == max) cnt++;
		}
		if(cnt >= 2) continue;
		if(ans == -1)
		{
			ans = maxi;
		}
		else
		{
			ans = -1;
			break;
		}
	}
	if(ans == -1)
	{
		printf("illegal");
	}
	else
	{
		printf("%d", ans);
	}
	return 0;
}