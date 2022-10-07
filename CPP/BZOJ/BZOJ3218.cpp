#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#define int long long
#define N 100000
const int inf = 0x7f7f7f7f;
int n, pool, p, len, s, t, base;
int d[N * 10];
int root[N + 5];
int head[N * 10 + 5];
int cur[N * 10 + 5];
struct Block
{
	int a, b, w, l, r, p;
} b[N + 5];
struct Edge
{
	int u, v, nxt, f;
} e[N * 20 + 5];
struct Node
{
	int l, r;
} tr[N * 10 + 5];
void add_edge(int u, int v, int f)
{
	e[p].u = u;
	e[p].v = v;
	e[p].f = f;
	e[p].nxt = head[u];
	head[u] = p++;
	e[p].u = v;
	e[p].v = u;
	e[p].f = 0;
	e[p].nxt = head[v];
	head[v] = p++;
}
void insert(int & k, int _k, int l, int r, int x, int v)
{
	k = ++pool;
	if(l == r)
	{
		if(k != 0) add_edge(k, _k, inf);
		add_edge(k, v, inf);
		return;
	}
	int mid = (l + r) >> 1; 
	if(x <= mid)
	{
		tr[k].r = tr[_k].r;
		insert(tr[k].l, tr[_k].l, l, mid, x, v);
	}
	else
	{
		tr[k].l = tr[_k].l;
		insert(tr[k].r, tr[_k].r, mid + 1, r, x, v);
	}
	if(tr[k].l != 0) add_edge(k, tr[k].l, inf);
	if(tr[k].r != 0) add_edge(k, tr[k].r, inf);
}
void modify(int k, int l, int r, int x, int y, int v)
{
	if(k == 0) return;
	if(x <= l && r <= y)
	{
		add_edge(v, k, inf);
		return;
	}
	int mid = (l + r) >> 1;
	if(x <= mid) modify(tr[k].l, l, mid, x, y, v);
	if(y > mid) modify(tr[k].r, mid + 1, r, x, y, v);
}
std::queue<int> q;
int dis[N * 10 + 5];
bool vis[N * 10 + 5];
bool bfs()
{
	memset(vis, 0, sizeof(vis));
	q.push(s);
	dis[s] = 0;
	vis[s] = true;
	while(!q.empty())
	{
		int u = q.front();
		q.pop();
		for(int i = head[u]; i != -1; i = e[i].nxt)
		{
			if(!vis[e[i].v] && e[i].f > 0)
			{
				vis[e[i].v] = true;
				dis[e[i].v] = dis[u] + 1;
				q.push(e[i].v);
			}
		}
	}
	return vis[t];
}
int dfs(int u, int rf)
{
	if(u == t || rf == 0) return rf;
	int flow = 0, f;
	for(int i = cur[u]; i != -1; i = e[i].nxt)
	{
		cur[u] = i;
		if(dis[u] + 1 == dis[e[i].v] && (f = dfs(e[i].v, std::min(e[i].f, rf))) > 0)
		{
			e[i].f -= f;
			e[i^1].f += f;
			flow += f;
			rf -= f;
			if(rf == 0) break;
		}
	}
	return flow;
}
int flow()
{
	int f = 0;
	while(bfs())
	{
		memcpy(cur, head, sizeof(cur));
		f += dfs(s, inf);
	}
	return f;
}
signed main()
{
	int ans = 0;
	memset(head, -1ll, sizeof(head));
	scanf("%lld", &n);
	for(int i = 1; i <= n; i++)
	{
		scanf("%lld%lld%lld%lld%lld%lld", &b[i].a, &b[i].b, &b[i].w, &b[i].l, &b[i].r, &b[i].p);
		ans += b[i].b + b[i].w;
		d[i * 3 - 2] = b[i].a;
		d[i * 3 - 1] = b[i].l;
		d[i * 3] = b[i].r;
	}
	std::sort(d + 1, d + 1 + 3 * n);
	len = std::unique(d + 1, d + 1 + 3 * n) - (d + 1);
	for(int i = 1; i <= n; i++)
	{
		b[i].a = std::lower_bound(d + 1, d + 1 + len, b[i].a) - d;
		b[i].l = std::lower_bound(d + 1, d + 1 + len, b[i].l) - d;
		b[i].r = std::lower_bound(d + 1, d + 1 + len, b[i].r) - d;
	}
	s = ++pool;
	t = ++pool;
	base = pool;
	for(int i = 1; i <= n; i++)
	{
		add_edge(s, i + pool, b[i].b);
		add_edge(i + pool, t, b[i].w);
		add_edge(i + pool, i + n + pool, b[i].p);
	}
	pool += 2 * n;
	for(int i = 1; i <= n; i++)
	{
		modify(root[i - 1], 1, len, b[i].l, b[i].r, i + n + base);
		insert(root[i], root[i - 1], 1, len, b[i].a, i + base);
	}
	printf("%lld", ans - flow());
	return 0;
}