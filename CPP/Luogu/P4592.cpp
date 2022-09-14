#include <cstdio>
#include <vector>
#define N 200000
struct node
{
	int l, r, val;
} t[30 * N + 5];
int n, q, pool;
int root[N + 5];
int val[N + 5];
std::vector<int> vec[N + 5];
int dep[N + 5];
int siz[N + 5];
int son[N + 5];
int fa[N + 5];
int seg[N + 5];
int rpr[N + 5];
int top[N + 5];
void dfs1(int u, int f)
{
	dep[u] = dep[f] + 1;
	siz[u] = 1;
	fa[u] = f;
	for(auto v : vec[u])
	{
		if(v == f) continue;
		dfs1(v, u);
		siz[u] += siz[v];
		if(siz[v] > siz[son[u]])
		{
			son[u] = v;
		}
	}
}
void dfs2(int u)
{
	if(son[u])
	{
		seg[son[u]] = ++seg[0];
		rpr[seg[0]] = son[u];
		top[son[u]] = top[u];
		dfs2(son[u]);
	}
	for(auto v : vec[u])
	{
		if(seg[v]) continue;
		seg[v] = ++seg[0];
		rpr[seg[0]] = v;
		top[v] = v;
		dfs2(v);
	}
}
void insert(int & k, int x, int d)
{
	t[++pool] = t[k];
	k = pool;
	t[k].val++;
	if(d == -1)
	{
		return;
	}
	if((1 << d) & x)
	{
		insert(t[k].r, x, d - 1);
	}
	else
	{
		insert(t[k].l, x, d - 1);
	}
}
int query(int k1, int k2, int z, int d)
{
	if(d == -1)
	{
		return z;
	}
	if((1 << d) & z)
	{
		if(t[t[k2].l].val - t[t[k1].l].val != 0)
		{
			return query(t[k1].l, t[k2].l, z, d - 1);
		}
		else
		{
			return query(t[k1].r, t[k2].r, z ^ (1 << d), d - 1);
		}
	}
	else
	{
		if(t[t[k2].r].val - t[t[k1].r].val != 0)
		{
			return query(t[k1].r, t[k2].r, z ^ (1 << d), d - 1);
		}
		else
		{
			return query(t[k1].l, t[k2].l, z, d - 1);
		}
	}
}
int ask(int x, int y, int z)
{
	int fx = top[x];
	int fy = top[y];
	int max = 0;
	while(fx != fy)
	{
		if(dep[fx] < dep[fy])
		{
			std::swap(fx, fy);
			std::swap(x, y);
		}
		max = std::max(max, query(root[seg[fx] - 1], root[seg[x]], z, 29));
		x = fa[fx];
		fx = top[x];
	}
	if(dep[x] > dep[y])
	{
		std::swap(x, y);
	}
	max = std::max(max, query(root[seg[x] - 1], root[seg[y]], z, 29));
	return max;
}
int main()
{
	scanf("%d%d", &n, &q);
	for(int i = 1; i <= n; i++)
	{
		scanf("%d", &val[i]);
	}
	for(int i = 1; i < n; i++)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		vec[u].push_back(v);
		vec[v].push_back(u);
	}
	dfs1(1, 0);
	seg[1] = seg[0] = rpr[1] = top[1] = 1;
	dfs2(1);
	for(int i = 1; i <= n; i++)
	{
		root[i] = root[i - 1];
		insert(root[i], val[rpr[i]], 29);
	}
	for(int i = 1; i <= q; i++)
	{
		int opt;
		scanf("%d", &opt);
		if(opt == 1)
		{
			int x, z;
			scanf("%d%d", &x, &z);
			printf("%d\n", query(root[seg[x] - 1], root[seg[x] + siz[x] - 1], z, 29));
		}
		else
		{
			int x, y, z;
			scanf("%d%d%d", &x, &y, &z);
			printf("%d\n", ask(x, y, z));
		}
	}
	return 0;
}