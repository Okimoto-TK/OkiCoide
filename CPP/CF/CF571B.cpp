#include <cstdio>
#include <cstring>
#include <algorithm>
#define N 300000
#define K 5000
const int mod = K + 2;
int n, k;
int x, y, z;
long long a[N + 5];
long long f[K + 5][K + 5];
long long val[N + 5];
long long sum[N + 5];
int main()
{
	scanf("%d%d", &n, &k);
	x = n % k;
	y = k - n % k;
	z = n / k;
	for(int i = 1; i <= n; i++)
	{
		scanf("%lld", &a[i]);
	}
	std::sort(a + 1, a + 1 + n);
	for(int i = 2; i <= n; i++)
	{
		val[i] = a[i] - a[i - 1];
		sum[i] = sum[i - 1] + val[i];
	}
	memset(f, 0x3f, sizeof(f));
	f[0][0] = 0;
	for(int i = 1; i <= k; i++)
	{
		for(int j = std::min(i, y); j >= 0; j--)
		{
			int _x = i - j;
			if(j > 0)
			{
				f[i][j] = std::min(f[i][j], f[i - 1][j - 1] + sum[z * j + (z + 1) * _x] - sum[z * (j - 1) + (z + 1) * _x + 1]);
			}
			f[i][j] = std::min(f[i][j], f[i - 1][j] + sum[z * j + (z + 1) * _x] - sum[z * j + (z + 1) * (_x - 1) + 1]);
		}
	}
	printf("%lld", f[k][y]);
	return 0;
} 
