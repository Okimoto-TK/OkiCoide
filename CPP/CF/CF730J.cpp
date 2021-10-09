#include <cstdio>
#include <cstring>
#include <algorithm>
int n, sum;
int a[105];
int b[105];
int _b[105];
int f[2][105][10005];
bool cmp(int a, int b) { return a > b; }
int main()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
	{
		scanf("%d", &a[i]);
		sum += a[i];
	}
	for(int i = 1; i <= n; i++)
	{
		scanf("%d", &b[i]);
		_b[i] = b[i];
	}
	std::sort(_b + 1, _b + 1 + n, cmp);
	int vol = 0;
	int k = 0;
	for(int i = 1; i <= n; i++)
	{
		vol += _b[i];
		k = i;
		if(vol >= sum) break;
	}
	printf("%d ", k);
	memset(f, 0xc0, sizeof(f));
	f[0][0][0] = 0;
	for(int i = 1; i <= n; i++)
	{
		memset(f[i % 2], 0xc0, sizeof(f[i % 2]));
		for(int j = 0; j <= k; j++)
		{
			for(int v = 0; v <= 10000; v++)
			{
				if(j == 0) f[i % 2][0][0] = 0;
				else
				{
					if(v < b[i]) f[i % 2][j][v] = f[(i + 1) % 2][j][v];
					else f[i % 2][j][v] = std::max(f[(i + 1) % 2][j - 1][v - b[i]] + a[i], f[(i + 1) % 2][j][v]);
				}
			}
		}
	}
	int ans = 0x3f3f3f3f;
	for(int i = sum; i <= 10000; i++)
	{
		if(f[n % 2][k][i] >= 0) ans = std::min(ans, sum - f[n % 2][k][i]);
	}
	printf("%d", ans);
	return 0;
}
