#include <cstdio>
#include <cstring>
#include <queue>
int n, m;
int p[1005][1005];
const int dir[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
bool vis[1005][1005];
struct node
{
	int x, y;
	node(int a, int b)
	{
		x = a;
		y = b;
	}
};
bool check(int x)
{
	std::queue<node> q;
	memset(vis, 0, sizeof(vis));
	for(int i = 1; i <= m; i++)
	{
		q.push(node(1, i));
		vis[1][i] = true;
	}
	while(!q.empty())
	{
		node u = q.front();
		if(u.x == n) return true;
		q.pop();
		for(int i = 0; i <= 3; i++)
		{
			node v = node(u.x + dir[i][0], u.y + dir[i][1]);
			if(v.x < 1 || v.x > n || v.y < 1 || v.y > m) continue;
			if(p[v.x][v.y] > x) continue;
			if(vis[v.x][v.y]) continue;
			q.push(v);
			vis[v.x][v.y] = true;
		}
	}
	return false;
}
int main()
{
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++)
	{
		for(int j = 1; j <= m; j++)
		{
			scanf("%d", &p[i][j]);
		}
	}
	int l = 0;
	int r = 1000;
	while(l < r)
	{
		int mid = (l + r) >> 1;
		if(check(mid))
		{
			r = mid;
		}
		else
		{
			l = mid + 1;
		}
	}
	printf("%d", l);
	return 0;
}
