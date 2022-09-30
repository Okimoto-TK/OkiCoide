#include <cstdio>
#include <cstring>
#include <queue>
#define N 1000000
#define int long long
int n, p;
int head[N + 5];
int a[N + 5];
struct Edge
{
	int v, nxt;
	long long w;
	Edge()
	{
		v = nxt = w = 0;
	}
	Edge(int x, int y, long long z)
	{
		v = x, nxt = y, w = z;
	}
} e[4 * N + 5];
void add_edge(int u, int v, long long w)
{
	e[++p].v = v;
	e[p].nxt = head[u];
	head[u] = p;
	e[p].w = w;
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
		u = x;
		w = y;
	}
	bool operator<(const item & x) const
	{
		return w > x.w;
	}
};
std::priority_queue<item> q;
long long dist[N + 5];
bool vis[N + 5];
long long dij(int s)
{
	memset(dist, 0x3f, sizeof(dist));
	dist[s] = 0;
	q.push(item(s, 0));
	while(!q.empty())
	{
		int u = q.top().u;
		q.pop();
		if(vis[u]) continue;
		vis[u] = true;
		for(int i = head[u]; i != -1; i = e[i].nxt)
		{
			int v = e[i].v;
			if(!vis[v] && dist[v] > dist[u] + e[i].w)
			{
				dist[v] = dist[u] + e[i].w;
				q.push(item(v, dist[v]));
			}
		}
	}
	return dist[n + 1];
}
signed main()
{
	memset(head, -1, sizeof(head));
	scanf("%lld", &n);
	for(int i = 1; i <= n; i++)
	{
		scanf("%lld", &a[i]);
		if(i + a[i] + 1 > n + 1)
		{
			add_edge(i, n + 1, i + a[i] - n);
		}
		else
		{
			add_edge(i, i + a[i] + 1, 0);
		}
		if(i == 1) continue;
		add_edge(i, i - 1, 1);
		add_edge(i, i + 1, 1);
	}
	printf("%lld", dij(1));
	return 0;
}
