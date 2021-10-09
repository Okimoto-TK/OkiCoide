#include <cstdio>
#include <cstring>
#include <algorithm>
int n, m;
char a[1005][1005];
int f[1005][1005];
bool vis[1005][1005];
int dx[] = {0, 1, -1, 0, 0};
int dy[] = {0, 0, 0, 1, -1};
bool check(char a, char b)
{
	if(a == 'D' && b == 'I') return true;
	if(a == 'I' && b == 'M') return true;
	if(a == 'M' && b == 'A') return true;
	if(a == 'A' && b == 'D') return true;
	return false;
}
bool isValid(int x, int y)
{
	return x <= n && x >= 1 && y <= m && y >= 1;
}
bool endless;
int dfs(int x, int y)
{
	if(vis[x][y]) endless = true;
	if(endless) return -1;
	if(f[x][y] >= 0) return f[x][y];
	vis[x][y] = true;
	int res = 0;
	for(int k = 1; k <= 4; k++)
	{
		int _x = x + dx[k];
		int _y = y + dy[k];
		if(isValid(_x, _y) && check(a[x][y], a[_x][_y])) res = std::max(res, dfs(_x, _y));
		if(endless) return -1;
	}
	vis[x][y] = false;
	return f[x][y] = (a[x][y] == 'A' ? 1 : 0) + res;
}
int main()
{
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++)
	{
		scanf("%s", a[i] + 1);
	}
	int ans = 0;
	memset(f, -1, sizeof(f));
	for(int i = 1; i <= n; i++)
	{
		for(int j = 1; j <= m; j++)
		{
			if(a[i][j] == 'D')
			{
				ans = std::max(ans, dfs(i, j));
				if(endless)
				{
					printf("Poor Inna!");
					return 0;
				}
			}
		}
	}
	if(ans == 0)
	{
		printf("Poor Dima!");
	}
	else
	{
		printf("%d", ans);
	}
	return 0;
}
