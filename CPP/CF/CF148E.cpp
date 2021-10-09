#include <cstdio>
#include <algorithm>
int n, m;
int k[105];
int a[105][105];
int f_sum[105][105];
int b_sum[105][105];
int f[105][105];
int g[10005];
int main()
{
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++)
	{
		scanf("%d", &k[i]);
		for(int j = 1; j <= k[i]; j++)
		{
			scanf("%d", &a[i][j]);
			f_sum[i][j] = f_sum[i][j - 1] + a[i][j];
		}
		for(int j = k[i]; j >= 1; j--) b_sum[i][j] = b_sum[i][j + 1] + a[i][j];
		for(int j = 1; j <= k[i]; j++)
		{
			for(int l = 0, r = j; l <= j; l++, r--)
			{
				f[i][j] = std::max(f[i][j], f_sum[i][l] + b_sum[i][k[i] - r + 1]);
			}
		}
	}
	for(int i = 1; i <= n; i++)
	{
		for(int j = m; j >= 0; j--)
		{
			for(int x = 0; x <= std::min(j, k[i]); x++)
			{
				g[j] = std::max(g[j], g[j - x] + f[i][x]);
			}
		}
	}
	printf("%d", g[m]);
	return 0;
}
