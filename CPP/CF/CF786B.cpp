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
void changeout(int k, int l, int r, int x, int y, int v, int val)
{
	if(x <= l && r <= y)
	{
		vec[k].push_back(Edge(v, val));
		return;
	}
	int mid = (l + r) >> 1;
	if(x <= mid) changeout(k << 1, l, mid, x, y, v, val);
	if(y > mid) changeout(k << 1 | 1, mid + 1, r, x, y, v, val);
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
void add(int a, int b, int c, int d, int w)
{
	int k = ++pool;
	changeout(1, 1, n, a, b, k, w);
	changein(1, 1, n, c, d, k);
}
long long dis[N * 10 + 5];
int vis[N * 10 + 5];
struct item
{
	int u;
	long long val;
	item()
	{
		u = val = 0;
	}
	item(int x, long long y)
	{
		u = x;
		val = y;
	}
	bool operator< (const item & x) const
	{
		return val > x.val;
	}
};
std::priority_queue<item> q;
void dij()
{
	memset(dis, 0x3f, sizeof(dis));
	q.push(item(s, 0));
	dis[s] = 0;
	while(!q.empty())
	{
		int u = q.top().u;
		//printf("%d ", u);
		q.pop();
		if(vis[u]) continue;
		vis[u] = true;
		for(auto v : vec[u])
		{
			if(dis[u] + v.w < dis[v.v])
			{
				dis[v.v] = dis[u] + v.w;
				if(!vis[v.v]) q.push(item(v.v, dis[v.v]));
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
		int op;
		int a, b, c, d;
		scanf("%d", &op);
		if(op == 1)
		{
			scanf("%d%d", &a, &c);
			b = a, d = c;
		}
		else if(op == 2)
		{
			scanf("%d%d%d", &a, &c, &d);
			b = a;
		}
		else
		{
			scanf("%d%d%d", &c, &a, &b);
			d = c;
		}
		int w;
		scanf("%d", &w);
		add(a, b, c, d, w);
	}
	dij();
	for(int i = 1; i <= n; i++)
	{
		printf("%lld\n", dis[ans[i]] >= 0x3f3f3f3f3f3f3f3f ? -1 : dis[ans[i]]);
	}
}
