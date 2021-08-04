#include <cstdio>
#include <algorithm>
const int ans[6][6] = {{0, 0, 0, 0, 0, 0}, {0, 1, 1, 1, 1, 1}, {0, 0, 1, 1, 1, 1}, {0, 0, 0, -1, 1, 1}, {0, 0, 0, 0, 0, 1}, {0, 0, 0, 0, 0, 0}};
const int mov[9][2] = {{0, 0}, {1, 2}, {2, 1}, {1, -2}, {2, -1}, {-2, 1}, {-1, 2}, {-2, -1}, {-1, -2}};
int a[6][6];
int count()
{
	int r = 0;
	for(int i = 1; i <= 5; i++)
	{
		for(int j = 1; j <= 5; j++)
		{
			r += (ans[i][j] == a[i][j]) ? 0 : 1;
		}
	}
	return r;
}
int limit;
bool dfs(int dep, int x, int y, int last)
{
	if(count() == 0) return true;
	if(dep == limit) return false;
	for(int i = 1; i <= 8; i++)
	{
		if(i + last == 9) continue;
		int _x = x + mov[i][0];
		int _y = y + mov[i][1];
		if(_x < 1 || _x > 5 || _y < 1 || _y > 5) continue;
		std::swap(a[x][y], a[_x][_y]);
		if(dep + count() <= limit) if(dfs(dep + 1, _x, _y, i)) return true;
		std::swap(a[x][y], a[_x][_y]);
	}
	return false;
} 
int main()
{
	int T;
	char buf[10];
	int x, y;
	for(scanf("%d", &T); T > 0; T--)
	{
		for(int i = 1; i <= 5; i++)
		{
			scanf("%5s", buf + 1);
			for(int j = 1; j <= 5; j++)
			{
				a[i][j] = (buf[j] == '*') ? -1 : buf[j] - '0';
				if(a[i][j] == -1) x = i, y = j;
			}
		}
		limit = 0;
		while(limit <= 15 && !dfs(0, x, y, 0)) limit++;
		if(limit <= 15) printf("%d\n", limit);
		else printf("-1\n");
	}
	return 0;
}
