#include <cstdio>
#include <vector>
#include <algorithm>
#define N 100005
int n, q;
int e[N];
std::vector<int> g[N];
int son[N];
int siz[N];
int dep[N];
int spr[N];
void dfs1(int u, int fa)
{
	spr[u] = fa;
	siz[u] = 1;
	dep[u] = dep[fa] + 1;
	int len = g[u].size();
	for(int i = 0; i < len; i++)
	{
		int v = g[u][i];
		if(v == fa) continue;
		dfs1(v, u);
		siz[u] += siz[v];
		if(siz[v] > siz[son[u]])
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
		int v = g[u][i];
		if(seg[v] != 0) continue;
		seg[v] = ++seg[0];
		rpr[seg[v]] = v;
		top[v] = v;
		dfs2(v);
	}
}
int tree[N << 2];
void build(int k, int l, int r)
{
	if(l == r)
	{
		tree[k] = e[rpr[l]];
		return;
	}
	int mid = (l + r) >> 1;
	build(k << 1, l, mid);
	build(k << 1 | 1, mid + 1, r);
	tree[k] = tree[k << 1] ^ tree[k << 1 | 1];
}
void change(int k, int l, int r, int x, int v)
{
	if(l == r)
	{
		tree[k] = v;
		return;
	}
	int mid = (l + r) >> 1;
	if(x <= mid) change(k << 1, l, mid, x, v);
	else change(k << 1 | 1, mid + 1, r, x, v);
	tree[k] = tree[k << 1] ^ tree[k << 1 | 1];
}
int query(int k, int l, int r, int x, int y)
{
	if(x <= l && r <= y)
	{
		return tree[k];
	}
	int mid = (l + r) >> 1;
	int res = 0;
	if(x <= mid) res ^= query(k << 1, l, mid, x, y);
	if(y > mid) res ^= query(k << 1 | 1, mid + 1, r, x, y);
	return res;
}
int ask(int x, int y)
{
	int fx = top[x];
	int fy = top[y];
	int res = 0;
	while(fx != fy)
	{
		if(dep[fx] < dep[fy])
		{
			std::swap(fx, fy);
			std::swap(x, y);
		}
		res ^= query(1, 1, seg[0], seg[fx], seg[x]);
		x = spr[fx];
		fx = top[x];
	}
	if(dep[x] > dep[y])
	{
		std::swap(x, y);
	}
	res ^= query(1, 1, seg[0], seg[x], seg[y]);
	return res;
}
int main()
{
	scanf("%d%d", &n, &q);
	for(int i = 1; i <= n; i++)
	{
		scanf("%d", &e[i]);
	}
	for(int i = 1; i < n; i++)
	{
		int a, b;
		scanf("%d%d", &a, &b);
		g[a].push_back(b);
		g[b].push_back(a);
	}
	dfs1(1, 0);
	seg[1] = seg[0] = rpr[1] = top[1] = 1;
	dfs2(1);
	build(1, 1, seg[0]);
	for(int i = 1; i <= q; i++)
	{
		int op, x, y;
		scanf("%d%d%d", &op, &x, &y);
		if(op == 1)
		{
			change(1, 1, seg[0], seg[x], y);	
		}
		else
		{
			printf("%d\n", ask(x, y));
		}
	}
	return 0;
}
