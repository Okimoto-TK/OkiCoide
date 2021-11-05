#include <cstdio>
#include <vector>
#include <algorithm>
#define N 50005
struct Edge
{
	int v, id;
	Edge() { v = id = 0; }
	Edge(int a, int b)
	{
		v = a;
		id = b;
	}
};
int n, m;
std::vector<Edge> g[N];
int siz[N];
int son[N];
int dep[N];
int spr[N];
int idx[N];
void dfs1(int u, int fa)
{
	siz[u] = 1;
	dep[u] = dep[fa] + 1;
	spr[u] = fa;
	int len = g[u].size();
	for(int i = 0; i < len; i++)
	{
		int v = g[u][i].v;
		if(v == fa) continue;
		idx[g[u][i].id] = v;
		dfs1(v, u);
		siz[u] += siz[v];
		if(siz[son[u]] < siz[v])
		{
			son[u] = v;
		}
	}
}
int seg[N];
int rpr[N];
int top[N];
void dfs2(int u)
{
	if(son[u] != 0)
	{
		int v = son[u];
		seg[v] = ++seg[0];
		rpr[seg[v]] = v;
		top[v] = top[u];
		dfs2(v);
	}
	int len = g[u].size();
	for(int i = 0; i < len; i++)
	{
		int v = g[u][i].v;
		if(seg[v] != 0) continue;
		seg[v] = ++seg[0];
		rpr[seg[v]] = v;
		top[v] = v;
		dfs2(v);
	}
}
int tree[N << 2];
int lazy[N << 2];
void build(int k, int l, int r)
{
	lazy[k] = 0x3f3f3f3f;
	if(l == r)
	{
		tree[k] = 0x3f3f3f3f;
		return;
	}
	int mid = (l + r) >> 1;
	build(k << 1, l, mid);
	build(k << 1 | 1, mid + 1, r);
	tree[k] = std::min(tree[k << 1], tree[k << 1 | 1]);
}
void minimize(int k, int v)
{
	tree[k] = std::min(tree[k], v);
	lazy[k] = std::min(lazy[k], v);
}
void push_down(int k)
{
	if(lazy[k] == 0x3f3f3f3f) return;
	minimize(k << 1, lazy[k]);
	minimize(k << 1 | 1, lazy[k]);
	lazy[k] = 0x3f3f3f3f;
}
void change(int k, int l, int r, int x, int y, int v)
{
	if(x <= l && r <= y)
	{
		minimize(k, v);
		return;
	}
	push_down(k);
	int mid = (l + r) >> 1;
	if(x <= mid) change(k << 1, l, mid, x, y, v);
	if(y > mid) change(k << 1 | 1, mid + 1, r, x, y, v);
	tree[k] = std::min(tree[k << 1], tree[k << 1 | 1]);
}
int query(int k, int l, int r, int x)
{
	if(l == r)
	{
		return tree[k];
	}
	push_down(k);
	int mid = (l + r) >> 1;
	if(x <= mid) return query(k << 1, l, mid, x);
	else return query(k << 1 | 1, mid + 1, r, x);
}
void modify(int x, int y, int w)
{
	int fx = top[x];
	int fy = top[y];
	while(fx != fy)
	{
		if(dep[fx] < dep[fy])
		{
			std::swap(fx, fy);
			std::swap(x, y);
		}
		change(1, 1, seg[0], seg[fx], seg[x], w);
		x = spr[fx];
		fx = top[x];
	}
	if(x == y) return;
	if(dep[x] > dep[y])
	{
		std::swap(x, y);
	}
	change(1, 1, seg[0], seg[x] + 1, seg[y], w);
}
int main()
{
	scanf("%d%d", &n, &m);
	for(int i = 1; i < n; i++)
	{
		int p, q;
		scanf("%d%d", &p, &q);
		g[p].push_back(Edge(q, i));
		g[q].push_back(Edge(p, i));
	}
	dfs1(1, 0);
	seg[1] = seg[0] = rpr[1] = top[1] = 1;
	dfs2(1);
	build(1, 1, seg[0]);
	for(int i = 1; i <= m; i++)
	{
		int u, v, w;
		scanf("%d%d%d", &u, &v, &w);
		modify(u, v, w);
	}
	for(int i = 1; i < n; i++)
	{
		int res = query(1, 1, seg[0], seg[idx[i]]);
		printf("%d\n", res == 0x3f3f3f3f ? -1 : res);
	}
	return 0;
}
