#include <cstdio>
#include <algorithm>
const int T[4][4] = {{0, 0, 0, 0}, {0, 1, 2, 3}, {0, 8, 0, 4}, {0, 7, 6, 5}};
const int Dx[4] = {1, 0, 0, -1};
const int Dy[4] = {0, 1, -1, 0};
int a[4][4];
int zerx, zery;
int count()
{
	int r = 0;
	for(int i = 1; i <= 3; i++)
	{
		for(int j = 1; j <= 3; j++)
		{
			r += (T[i][j] == a[i][j]) ? 0 : 1;
		}
	}
	return r;
}
int limit;
bool dfs(int dep, int x, int y, int last)
{
	if(count() == 0) return true;
	if(dep >= limit) return false;
	for(int i = 0; i < 4; i++)
	{
		int _x = x + Dx[i];
		int _y = y + Dy[i];
		if(_x < 1 || _x > 3 || _y < 1 || _y > 3 || last + i == 3) continue;
		std::swap(a[x][y], a[_x][_y]);
		if(dep + count() <= limit)
		{
			if(dfs(dep + 1, _x, _y, i)) return true;
		}
		std::swap(a[x][y], a[_x][_y]);
	}
	return false;
}
int main()
{
	for(int i = 1; i <= 3; i++)
	{
		for(int j = 1; j <= 3; j++)
		{
			scanf("%1d", &a[i][j]);
			if(a[i][j] == 0) zerx = i, zery = j;
		}
	}
	limit = 0;
	while(!dfs(0, zerx, zery, -1)) limit++;
	printf("%d", limit);
	return 0;
}
