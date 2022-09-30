#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
int n, cnt, p, min;
long long l, r;
int a[20];
int head[500005];
struct Edge
{
	int v, nxt;
	int w;
	Edge()
	{
		v = nxt = w = 0;
	}
	Edge(int x, int y, int z)
	{
		v = x;
		nxt = y;
		w = z;
	}
} e[5000005];
void add_edge(int u, int v, int w)
{
	e[++p].v = v;
	e[p].nxt = head[u];
	e[p].w = w;
	head[u] = p;
}
struct item
{
	int u;
	long long w;
	item()
	{
		u = w = 0;
	}
	item(int x, long long y)
	{
		u = x, w = y;
	}
	bool operator<(const item & x) const
	{
		return w > x.w;
	}
};
std::priority_queue<item> q;
long long dist[500005];
bool vis[500005];
void dij(int s)
{
	memset(dist, 0x3f, sizeof(dist));
	q.push(item(s, 0));
	dist[s] = 0;
	while(!q.empty())
	{
		int u = q.top().u;
		q.pop();
		if(vis[u]) continue;
		vis[u] = true;
		for(int i = head[u]; i != -1; i = e[i].nxt)
		{
			dist[e[i].v] = std::min(dist[e[i].v], dist[u] + e[i].w);
			if(!vis[e[i].v])
			{
				q.push(item(e[i].v, dist[e[i].v]));
			}
		}
	}
}
long long query(long long x)
{
	long long re = 0;
	for(int i = 0; i < min; i++)
	{
		if(dist[i] <= x)
		{
			re += (x - dist[i]) / min + 1;
			printf("%d %d\n", x, (x - dist[i]) / min + 1);
		}
	}
	return re;
}
signed main()
{
	memset(head, -1, sizeof(head));
	scanf("%d %lld %lld", &n, &l, &r);
	min = 1e18 + 7;
	for(int i = 1; i <= n; i++)
	{
		int x;
		scanf("%d", &x);
		if(x)
		{
			a[++cnt] = x;
			min = std::min(min, x);
		}
	}
	for(int i = 0; i < min; i++)
	{
		for(int j = 1; j <= cnt; j++)
		{
			if(a[j] == min) continue;
			add_edge(i, (i + a[j]) % min, a[j]);
		}
	}
	dij(0);
	printf("%lld", query(r) - query(l - 1));
	return 0;
}
