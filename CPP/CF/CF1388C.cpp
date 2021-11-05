#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <vector>
int t;
int n, m;
bool valid = true;
int p[200005];
int h[200005];
int s[200005];
int hp[200005];
std::vector<int> g[200005];
void init()
{
	valid = true;
	for(int i = 0; i <= n; i++)
	{
		g[i].clear();
	}
}
void dfs(int u, int fa)
{
	int len = g[u].size();
	int hpsum = 0;
	s[u] = p[u];
	for(int i = 0; i < len; i++)
	{
		int v = g[u][i];
		if(v == fa) continue;
		dfs(v, u);
		hpsum += hp[v];
		s[u] += s[v];
	}
	if(abs(h[u]) > s[u]) valid = false;
	if((s[u] + h[u]) % 2 == 1) valid = false;
	hp[u] = (s[u] + h[u]) / 2;
	if(hpsum > hp[u]) valid = false;
}
signed main()
{
	for(scanf("%d", &t); t != 0; t--)
	{
		scanf("%d%d", &n, &m);
		init();
		for(int i = 1; i <= n; i++) scanf("%d", &p[i]);
		for(int i = 1; i <= n; i++) scanf("%d", &h[i]);
		for(int i = 1; i < n; i++)
		{
			int x, y;
			scanf("%d%d", &x, &y);
			g[x].push_back(y);
			g[y].push_back(x);
		}
		dfs(1, 0);
		if(!valid)
		{
			printf("NO\n");
			continue;
		}
		printf("YES\n");
	}
	return 0;
}
