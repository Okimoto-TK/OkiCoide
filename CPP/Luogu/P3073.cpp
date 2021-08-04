#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <queue>
int n, k;
int h[505][505];
bool vis[505][505];
const int dir[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
struct pos
{
	int x, y;
	pos(int a, int b)
	{
		x = a;
		y = b;
	}
};
bool check(int x)
{
	memset(vis, 0, sizeof(vis));
	int cntmax = 0;
	std::queue<pos> q;
	for(int i = 1; i <= n; i++)
	{
		for(int j = 1; j <= n; j++)
		{
			if(!vis[i][j])
			{
				q.push(pos(i, j));
				vis[i][j] = true;
				int cnt = 1;
				while(!q.empty())
				{
					pos u = q.front();
					q.pop();
					for(int d = 0; d <= 3; d++)
					{
						int _x = u.x + dir[d][0];
						int _y = u.y + dir[d][1];
						if(_x < 1 || _x > n || _y < 1 || _y > n) continue;
						if(vis[_x][_y]) continue;
						if(abs(h[_x][_y] - h[u.x][u.y]) <= x)
						{
							q.push(pos(_x, _y));
							vis[_x][_y] = true;
							cnt++;
						}
					}
				}
				cntmax = cntmax > cnt ? cntmax : cnt;
			}
		}
	}
	return cntmax >= k;
}
int main()
{
	scanf("%d", &n);
	if(n % 2 == 1) k = n * n / 2 + 1;
	else k = n * n / 2;
	for(int i = 1; i <= n; i++)
	{
		for(int j = 1; j <= n; j++)
		{
			scanf("%d", &h[i][j]);
		}
	}
	int l = 0;
	int r = 1000005;
	while(l < r)
	{
		int mid = (l + r) >> 1;
		if(check(mid)) r = mid;
		else l = mid + 1;
	}
	printf("%d", l);
	return 0;
}
