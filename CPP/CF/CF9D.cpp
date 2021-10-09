#include <cstdio>
#include <cstring>
int n, h;
long long f[40][40];
int main()
{
	scanf("%d%d", &n, &h);
	for(int i = 0; i <= n; i++) f[0][i] = 1ll;
	for(int i = 1; i <= n; i++)
	{
		for(int j = 1; j <= n; j++)
		{
			for(int k = 0; k < j; k++)
			{
				f[j][i] += f[k][i - 1] * f[j - k - 1][i - 1];
			}
		}
	}
	printf("%lld", f[n][n] - f[n][h - 1]);
	return 0;
}
