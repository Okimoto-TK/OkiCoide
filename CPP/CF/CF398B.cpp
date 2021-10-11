#include <cstdio>
#include <algorithm>
#define N 2005
int n, m, ipre, jpre;
bool r[N];
bool c[N];
double e[N][N];
int main()
{
	scanf("%d%d", &n, &m);
	ipre = jpre = n;
	for(int i = 1; i <= m; i++)
	{
		int x, y;
		scanf("%d%d", &x, &y);
		if(!r[x])
		{
			r[x] = true;
			ipre--;
		}
		if(!c[y])
		{
			c[y] = true;
			jpre--;
		}
	}
	for(int i = 1; i <= n; i++) e[i][0] = e[0][i] = e[i - 1][0] + double(n) / i;
	for(int i = 1; i <= n; i++)
	{
		for(int j = 1; j <= n; j++)
		{
			e[i][j] = double(n * n + i * j * e[i - 1][j - 1] + i * (n - j) * e[i - 1][j] + (n - i) * j * e[i][j - 1]) / double(n * i + n * j - i * j);
		}
	}
	printf("%lf", e[ipre][jpre]);
	return 0;
}
