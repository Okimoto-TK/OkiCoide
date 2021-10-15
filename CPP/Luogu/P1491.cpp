#include <cstdio>
#include <cmath>
#include <cstring>
#include <queue>
#include <vector>
struct Point
{
	int x, y;
} p[205];
int n, m;
bool con[205][205];
int re_path[205];
std::vector<int> g[205];
void build()
{
	for(int i = 1; i <= n; i++) g[i].clear();
	for(int i = 1; i <= n; i++)
	{
		for(int j = 1; j <= n; j++)
		{
			if(con[i][j]) g[i].push_back(j);
		}
	}
}
double getDist(Point a, Point b)
{
	return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}
void Dij1()
{
	double dis[205];
	memset(dis, 0x42, sizeof(dis));
	bool vis[205];
	memset(vis, 0, sizeof(vis));
	std::priority_queue<std::pair<double, int>, std::vector<std::pair<double, int> >, std::greater<std::pair<double, int> > > q;
	q.push(std::make_pair(0, 1));
	dis[1] = 0;
	while(!q.empty())
	{
		double w = q.top().first;
		int u = q.top().second;
		q.pop();
		if(vis[u]) continue;
		vis[u] = true;
		for(auto v : g[u])
		{
			double _w = getDist(p[u], p[v]);
			if(_w + w < dis[v])
			{
				dis[v] = _w + w;
				re_path[v] = u;
				q.push(std::make_pair(dis[v], v));
			}
		}
	}
}
double Dij2()
{
	double dis[205];
	memset(dis, 0x42, sizeof(dis));
	bool vis[205];
	memset(vis, 0, sizeof(vis));
	std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int> >, std::greater<std::pair<int, int> > > q;
	q.push(std::make_pair(0, 1));
	dis[1] = 0;
	while(!q.empty())
	{
		int u = q.top().second;
		q.pop();
		if(vis[u]) continue;
		vis[u] = true;
		for(auto v : g[u])
		{
			if(dis[u] + getDist(p[u], p[v]) < dis[v])
			{
				dis[v] = dis[u] + getDist(p[u], p[v]);
				q.push(std::make_pair(dis[v], v));
			}
		}
	}
	return dis[n];
}
int main()
{
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++) scanf("%d%d", &p[i].x, &p[i].y);
	for(int i = 1; i <= m; i++)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		con[u][v] = con[v][u] = true;
	}
	build();
	Dij1();
	double ans = 1e9;
	for(int i = 1; i <= n; i++) g[i].clear();
	for(int i = n; i != 1; i = re_path[i])
	{
		con[i][re_path[i]] = con[re_path[i]][i] = false;
		build();
		ans = std::min(ans, Dij2());
		con[i][re_path[i]] = con[re_path[i]][i] = true;
	}
	if(ans < 1e9) printf("%.2lf", ans);
	else printf("-1");
	return 0;
}
