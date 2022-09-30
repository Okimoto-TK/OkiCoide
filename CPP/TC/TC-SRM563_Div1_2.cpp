#include <cstdio>
#include <algorithm>
int n;
int v[55];
int w[55];
int f[55][55];
int main()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
	{
		scanf("%d", &w[i]);
	}
	for(int i = 1; i <= n; i++)
	{
		scanf("%d", &v[i]);
	}
	for(int i = 1; i <= n; i++)
	{
		for(int j = n; j >= 0; j--)
		{
			f[i][j] = f[i - 1][j];
			if(j >= w[i]) f[i][j] = std::max(f[i][j], f[i - 1][j - w[i]] + v[i]);
		}
	}
	int max = 0;
	for(int i = 1; i <= n; i++)
	{
		for(int j = 1; j <= n; j++)
		{
			max = std::max(f[i][j], max);
		}
	}
	printf("%d", max);
	return 0;
}
