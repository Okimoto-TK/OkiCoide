#include <cstdio>
#include <cstring>
#include <algorithm>
#define N 2000000
#define P 1000000007
long long f[2000005][2];
int main()
{
	memset(f, 0xc0, sizeof(f));
	f[1][0] = 0;
	f[1][1] = 0;
	f[2][0] = 0;
	f[2][1] = 0;
	for(int i = 3; i <= N; i++)
	{
		f[i][0] = 2 * std::max(f[i - 2][1], f[i - 2][0]) + std::max(f[i - 1][0], f[i - 1][1]);
		f[i][0] %= P;
		f[i][1] = 2 * f[i - 2][0] + f[i - 1][0] + 4;
		f[i][1] %= P;
	}
	int t;
	for(scanf("%d", &t); t != 0; t--)
	{
		int n;
		scanf("%d", &n);
		printf("%lld\n", std::max(f[n][0], f[n][1]));
	}
	return 0;
}
