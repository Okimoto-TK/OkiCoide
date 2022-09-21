#include <cstdio>
#include <vector>
#include <algorithm>
#define N 100000
int n, m, pool;
struct node
{
	int l, r;
	int max, val;
} t[N * 100];
int root[N + 5];
std::vector<int> vec[N + 5];
int lca[N + 5][20];
int dep[N + 5];
void dfs1(int u, int fa)
{
	dep[u] = dep[fa] + 1;
	lca[u][0] = fa;
	for(int i = 1; i <= 18; i++)
	{
		lca[u][i] = lca[lca[u][i - 1]][i - 1];
	}
	for(auto v : vec[u])
	{
		if(v == fa) continue;
		dfs1(v, u);
	}
}
void push_up(int k)
{
	//printf("%d %d %d %d\n", t[t[k].l].val, t[t[k].l].max, t[t[k].r].val, t[t[k].r].max);
	if(t[t[k].l].max >= t[t[k].r].max)
	{
		t[k].val = t[t[k].l].val;
		t[k].max = t[t[k].l].max;
	}
	else
	{
		t[k].val = t[t[k].r].val;
		t[k].max = t[t[k].r].max;
	}
}
void change(int & k, int l, int r, int x, int v)
{
	if(k == 0)
	{
		k = ++pool;
	}
	if(l == r)
	{
		t[k].val = l;
		t[k].max += v;
		return;
	}
	int mid = (l + r) >> 1;
	if(x <= mid)
	{
		change(t[k].l, l, mid, x, v);
	}
	else
	{
		change(t[k].r, mid + 1, r, x, v);
	}
	push_up(k);
}
void merge(int & k, int _k, int l, int r)
{
	if(k == 0 || _k == 0)
	{
		k += _k;
		return;
	}
	if(l == r)
	{
		t[k].val = l;
		t[k].max += t[_k].max;
		return;
	}
	int mid = (l + r) >> 1;
	merge(t[k].l, t[_k].l, l, mid);
	merge(t[k].r, t[_k].r, mid + 1, r);
	push_up(k);
}
int query(int k)
{
	return t[k].max <= 0 ? 0 : t[k].val;
}
int Lca(int x, int y)
{
	if(dep[x] < dep[y])
	{
		std::swap(x, y);
	}
	for(int i = 18; i >= 0; i--)
	{
		if(dep[lca[x][i]] >= dep[y])
		{
			x = lca[x][i];
		}
	}
	if(x == y) return x;
	for(int i = 18; i >= 0; i--)
	{
		if(lca[x][i] != lca[y][i])
		{
			x = lca[x][i];
			y = lca[y][i];
		}
	}
	return lca[x][0];
}
void modify(int x, int y, int z)
{
	if(dep[x] > dep[y])
	{
		std::swap(x, y);
	}
	int c = Lca(x, y);
	if(x == c)
	{
		change(root[y], 1, N, z, 1);
		change(root[lca[c][0]], 1, N, z, -1);
	}
	else
	{
		change(root[x], 1, N, z, 1);
		change(root[y], 1, N, z, 1);
		change(root[c], 1, N, z, -1);
		change(root[lca[c][0]], 1, N, z, -1);
	}
}
int ans[N + 5];
void dfs2(int u, int fa)
{
	for(auto v : vec[u])
	{
		if(v == fa) continue;
		dfs2(v, u);
		merge(root[u], root[v], 1, N);
	}
	ans[u] = query(root[u]);
}
int main()
{
	scanf("%d%d", &n, &m);
	for(int i = 1; i < n; i++)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		vec[u].push_back(v);
		vec[v].push_back(u);
	}
	dfs1(1, 0);
	for(int i = 1; i <= m; i++)
	{
		int x, y, z;
		scanf("%d%d%d", &x, &y, &z);
		modify(x, y, z);
	}
	dfs2(1, 0);
	for(int i = 1; i <= n; i++)
	{
		printf("%d\n", ans[i]);
	}
	return 0;
}
