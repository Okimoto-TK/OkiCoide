#include <cstdio>
#include <cstring>
#include <algorithm>
int n, m;
int f[105][105];
int d1[105];
int d2[105];
bool check(int x)
{
	memset(f, ~0x3f, sizeof(f));
	f[0][0] = 0;
	for(int i = 1; i <= n; i++)
	{
		for(int j = 0; j <= m; j++)
		{
			for(int y = 0, c = 0; y <= x; y += d1[i], c++)
			{
				if(j - c >= 0) f[i][j] = std::max(f[i][j], f[i - 1][j - c] + (x - y) / d2[i]);
			}
		}
	}
	return f[n][m] >= m;
}
int main()
{
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++)
	{
		scanf("%d%d", &d1[i], &d2[i]);
	}
	int l = 0;
	int r = 200;
	while(l < r)
	{
		int mid = (l + r) >> 1;
		if(check(mid)) r = mid;
		else l = mid + 1;
	}
	printf("%d", l);
	return 0;
}
