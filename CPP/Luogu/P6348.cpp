#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>
#define N 500000
#define B 2000000
int n, m, p, pool, s;
int ans[N + 5];
struct Edge
{
	int v, w;
	Edge()
	{
		v = w = 0;
	}
	Edge(int _v)
	{
		v = _v;
		w = 0;
	}
	Edge(int _v, int _w)
	{
		v = _v;
		w = _w;
	}
};
std::vector<Edge> vec[N * 10 + 5];
void buildout(int k, int l, int r)
{
	if(l == r)
	{
		return;
	}
	int mid = (l + r) >> 1;
	vec[k << 1].push_back(Edge(k));
	vec[k << 1 | 1].push_back(Edge(k));
	buildout(k << 1, l, mid);
	buildout(k << 1 | 1, mid + 1, r);
}
void buildin(int k, int l, int r)
{
	vec[k + B].push_back(Edge(k));
	if(l == r)
	{
		if(l == p) s = k + B;
		ans[l] = k + B;
		return;
	}
	vec[k + B].push_back(Edge((k << 1) + B));
	vec[k + B].push_back(Edge((k << 1 | 1) + B));
	int mid = (l + r) >> 1;
	buildin(k << 1, l, mid);
	buildin(k << 1 | 1, mid + 1, r);
}
void changeout(int k, int l, int r, int x, int y, int v)
{
	if(x <= l && r <= y)
	{
		vec[k].push_back(Edge(v, 1));
		return;
	}
	int mid = (l + r) >> 1;
	if(x <= mid) changeout(k << 1, l, mid, x, y, v);
	if(y > mid) changeout(k << 1 | 1, mid + 1, r, x, y, v);
}
void changein(int k, int l, int r, int x, int y, int v)
{
	if(x <= l && r <= y)
	{
		vec[v].push_back(Edge(k + B, 0));
		return;
	}
	int mid = (l + r) >> 1;
	if(x <= mid) changein(k << 1, l, mid, x, y, v);
	if(y > mid) changein(k << 1 | 1, mid + 1, r, x, y, v);
}
void add(int a, int b, int c, int d)
{
	int k = ++pool;
	changeout(1, 1, n, a, b, k);
	changein(1, 1, n, c, d, k);
	k = ++pool;
	changein(1, 1, n, a, b, k);
	changeout(1, 1, n, c, d, k);
}
int dis[N * 10 + 5];
int vis[N * 10 + 5];
std::deque<int> q;
void bfs()
{
	memset(dis, 0x3f3f3f3f, sizeof(dis));
	dis[s] = 0;
	q.push_back(s);
	while(!q.empty())
	{
		int u = q.front();
		q.pop_front();
		if(vis[u])
		{
			continue;
		}
		//printf("%d ", u);
		vis[u] = true;
		for(auto v : vec[u])
		{
			//printf("%d %d\n", u, v.v);
			if(dis[u] + v.w < dis[v.v])
			{
				dis[v.v] = dis[u] + v.w;
				if(v.w == 0)
				{
					q.push_front(v.v);
				}
				else
				{
					q.push_back(v.v);
				}
			}
		}
	}
}
int main()
{
	scanf("%d%d%d", &n, &m, &p);
	buildout(1, 1, n);
	buildin(1, 1, n);
	pool = 4000000;
	for(int i = 1; i <= m; i++)
	{
		int a, b, c, d;
		scanf("%d%d%d%d", &a, &b, &c, &d);
		add(a, b, c, d);
	}
	bfs();
	for(int i = 1; i <= n; i++)
	{
		printf("%d\n", dis[ans[i]]);
	}
}
