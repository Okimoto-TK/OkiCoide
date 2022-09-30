#include <cstdio>
#include <algorithm>
#define N 5000
double f[N + 5][N + 5];
double dfs(int n, int m)
{
	if(n == 0 && m == 0) return 0;
	if(f[n][m] >= 0) return f[n][m];
	if(n == 0) return 0;
	if(m == 0) return n;
	return f[n][m] = std::max(double(n) / double(n + m) * (dfs(n - 1, m) + 1) + double(m) / double(n + m) * (dfs(n, m - 1) - 1), 0.0);
}
int main()
{
	int n, m;
	scanf("%d%d", &n, &m);
	for(int i = 0; i <= n; i++)
	{
		for(int j = 0; j <= m; j++)
		{
			f[i][j] = -1;
		}
	}
	printf("%.10f", dfs(n, m));
}
