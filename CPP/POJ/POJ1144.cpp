#include <cstdio>
#include <cstring>
#include <algorithm>
int n, pool;
bool edge[105][105];
int dfn[105];
int low[105];
bool cut[105];
void tarjan(int u)
{
	dfn[u] = low[u] = ++pool;
	int cnt = 0;
	for(int v = 1; v <= n; v++)
	{
		if(edge[u][v])
		{
			if(!dfn[v])
			{
				cnt++;
				tarjan(v);
				low[u] = std::min(low[v], low[u]);
				if((u == 1 && cnt > 1) || (u != 1 && dfn[u] <= low[v]))
				{
					cut[u] = true;
				}
			}
			else low[u] = std::min(low[u], dfn[v]);
		}
	}
	//printf("%d %d %d\n", u, dfn[u], low[u]);
}
int main()
{
	for(scanf("%d", &n); n != 0; scanf("%d", &n))
	{
		memset(edge, 0, sizeof(edge));
		memset(dfn, 0, sizeof(dfn));
		memset(low, 0, sizeof(low));
		memset(cut, 0, sizeof(cut));
		pool = 0;
		int x;
		for(scanf("%d", &x); x != 0; scanf("%d", &x))
		{
			scanf("%c", new char);
			char buf[512];
			scanf("%[^\n]\n", buf);
			int len = strlen(buf);
			int a = 0;
			for(int i = 0; i < len; i++)
			{
				if(buf[i] >= '0' && buf[i] <= '9')
				{
					a *= 10;
					a += buf[i] - '0';
				}
				else
				{
					//printf("%d\n", a);
					edge[x][a] = edge[a][x] = true;
					a = 0;
				}
			}
			if(a != 0) edge[x][a] = edge[a][x] = true;
		}
		tarjan(1);
		int ans = 0;
		for(int i = 1; i <= n; i++)
		{
			if(cut[i]) ans++;
		}
		printf("%d\n", ans);
	}
	return 0;
}