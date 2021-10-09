#include <cstdio>
#include <cstring>
#include <algorithm>
#include <string>
int n, m, k;
int a[105][105];
int f[105][105][20];
int g[105][105][20][3];
void Update(int &x, int y, int r, int i, int j, int _j, int _r)
{
	if(x < y)
	{
		x = y;
		g[i][j][r][0] = i + 1;
		g[i][j][r][1] = _j;
		g[i][j][r][2] = _r;
	}
}
int main()
{
	memset(f, 0x80, sizeof(f));
	scanf("%d%d%d", &n, &m, &k);
	for(int i = 1; i <= n; i++)
	{
		for(int j = 1; j <= m; j++) scanf("%1d", &a[i][j]);
	}
	for(int i = 1; i <= m; i++)
	{
		f[n][i][a[n][i] % (k + 1)] = a[n][i];
	}
	for(int i = n - 1; i >= 1; i--)
	{
		for(int j = 1; j <= m; j++)
		{
			for(int x = j - 1; x <= j + 1; x += 2)
			{
				for(int r = 0; r <= k; r++)
				{
					Update(f[i][j][(a[i][j] + r) % (k + 1)], f[i + 1][x][r] + a[i][j], (a[i][j] + r) % (k + 1), i, j, x, r);
				}
			}
		}
	}
	int ans = -1;
	int ptr = 0;
	int r = 0;
	for(int i = 1; i <= m; i++)
	{
		if(ans < f[1][i][0])
		{
			ans = f[1][i][0];
			ptr = i;
		}
	}
	if(ptr == 0)
	{
		printf("-1");
		return 0;
	}
	printf("%d\n", ans);
	std::string path_str = "";
	for(int i = 1; i < n; i++)
	{
		int from = g[i][ptr][r][1];
		r = g[i][ptr][r][2];
		if(from < ptr) path_str = "R" + path_str;
		else path_str = "L" + path_str;
		ptr = from;
	}
	printf("%d\n%s", ptr, path_str.c_str());
	return 0;
}
