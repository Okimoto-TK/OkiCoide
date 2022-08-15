#include <cstdio>
#include <cstring>
#define N 10000
const long long mod = 1000000007;
int n;
int h[N + 5];
long long f[2][N + 5];
inline void qmod(long long & x)
{
	if(x >= 1e16)
	{
		x %= mod;
	}
}
int main()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
	{
		scanf("%d", &h[i]);
	}
	if(h[1] != 0 && h[1] != -1)
	{
		printf("%d", 0);
		return 0;
	}
	f[1][0] = 1;
	for(int i = 2; i <= n; i++)
	{	
		if(h[i] == -1)
		{
			for(int j = 0; j <= n; j++)
			{
				f[i & 1][j] = 0;
				f[i & 1][j] += f[(i & 1) ^ 1][j];
				if(j != 0)
				{
					f[i & 1][j] += f[(i & 1) ^ 1][j - 1];
				}
				f[i & 1][j] += f[(i & 1) ^ 1][j + 1];
				qmod(f[i & 1][j]);
			}
		}
		else
		{
			for(int j = 0; j <= n; j++)
			{
				f[i & 1][j] = 0;
			}
			f[i & 1][h[i]] = 0;
			f[i & 1][h[i]] += f[(i & 1) ^ 1][h[i]];
			if(h[i] != 0)
			{
				f[i & 1][h[i]] += f[(i & 1) ^ 1][h[i] - 1];
			}
			f[i & 1][h[i]] += f[(i & 1) ^ 1][h[i] + 1];
			qmod(f[i & 1][h[i]]);
		}
	}
	printf("%d", f[n & 1][0] % mod); 
	return 0;
}
