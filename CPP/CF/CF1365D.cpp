#include <cstdio>
#include <cstring>
#include <queue>
int n, m;
char a[60][60];
bool vis[60][60];
std::queue<std::pair<int, int> > q;
int main()
{
	int t;
	for(scanf("%d", &t); t != 0; t--)
	{
		scanf("%d%d", &n, &m);
		memset(a, 0, sizeof(a));
		memset(vis, 0, sizeof(vis));
		for(int i = 1; i <= n; i++)
		{
			scanf("%s", a[i] + 1);
		}
		int cnt = 0;
		for(int i = 1; i <= n; i++)
		{
			for(int j = 1; j <= m; j++)
			{
				if(a[i][j] == 'B')
				{
					if(i != 1) vis[i - 1][j] = true;
					if(i != n) vis[i + 1][j] = true;
					if(j != 1) vis[i][j - 1] = true;
					if(j != m) vis[i][j + 1] = true;
				}
				else if(a[i][j] == '#') vis[i][j] = true;
				else if(a[i][j] == 'G') cnt++;
			}
		}
		while(!q.empty()) q.pop();
		q.push(std::make_pair(n, m));
		int ans = 0;
		while(!q.empty())
		{
			int x = q.front().first;
			int y = q.front().second;
			q.pop();
			if(vis[x][y]) continue;
			vis[x][y] = true;
			if(a[x][y] == 'G') ans++;
			if(x != 1) q.push(std::make_pair(x - 1, y));
			if(x != n) q.push(std::make_pair(x + 1, y));
			if(y != 1) q.push(std::make_pair(x, y - 1));
			if(y != m) q.push(std::make_pair(x, y + 1));
		}
		printf("%s\n", ans == cnt ? "Yes" : "No");
	}
	return 0;
}
