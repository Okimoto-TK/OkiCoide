#include <cstdio>
#include <cstring>
int n;
int a[5005];
int sum[5005];
int f[5005][2];
int main()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
	{
		scanf("%d", &a[i]);
		sum[i] = sum[i - 1] + a[i];
	}
	f[0][0] = f[0][1] = 0;
	for(int i = 1; i <= n; i++)
	{
		for(int j = i - 1; j >= 0; j--)
		{
			if(sum[i] - sum[j] >= f[j][1])
			{
				f[i][0] = f[j][0] + 1;
				f[i][1] = sum[i] - sum[j];
				break;
			}
		}
	}
	printf("%d", n - f[n][0]);
	return 0;
}
