#include <cstdio>
#include <vector>
#define N 500000
struct node
{
	int l, r, cnt, sum;
} t[62 * N + 5];
int n, m, pool;
std::vector<int> vec[N + 5];
int val[N + 5];
int fa[N + 5];
int lazy[N + 5];
int root[N + 5];
void dfs(int u, int f)
{
	fa[u] = f;
	for(auto v : vec[u])
	{
		if(v == f) continue;
		dfs(v, u);
	}
}
void update(int k, int d)
{
	t[k].sum = ((t[t[k].r].cnt & 1) << d) | (t[t[k].l].sum ^ t[t[k].r].sum);
}
void insert(int & k, int x, int d, int w)
{
	if(k == 0)
	{
		k = ++pool;
	}
	t[k].cnt += w;
	if(d == 20)
	{
		return;
	}
	if((1 << d) & x)
	{
		insert(t[k].r, x, d + 1, w);
	}
	else
	{
		insert(t[k].l, x, d + 1, w);
	}
	update(k, d);
}
void change(int k, int d)
{
	if(d == 20)
	{
		return;
	}
	std::swap(t[k].l, t[k].r);
	if(t[k].l != 0)
	{
		change(t[k].l, d + 1);
	}
	update(k, d);
	
}
int query(int k)
{
	return t[k].sum;
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
	dfs(1, 0);
	for(int i = 1; i <= n; i++)
	{
		scanf("%d", &val[i]);
		if(fa[i] != 0)
		{
			insert(root[fa[i]], val[i], 0, 1);
		}
	}
	for(int i = 1; i <= m; i++)
	{
		int opt;
		scanf("%d", &opt);
		if(opt == 1)
		{
			int x;
			scanf("%d", &x);
			change(root[x], 0);
			if(fa[fa[x]] != 0)
			{
				insert(root[fa[fa[x]]], val[fa[x]] + lazy[fa[fa[x]]], 0, -1);
				insert(root[fa[fa[x]]], val[fa[x]] + 1 + lazy[fa[fa[x]]], 0, 1);
			}
			lazy[x]++;
			if(fa[x] != 0)
			{
				val[fa[x]]++;
			}
		}
		else if(opt == 2)
		{
			int x, v;
			scanf("%d%d", &x, &v);
			if(fa[x])
			{
				insert(root[fa[x]], val[x] + lazy[fa[x]], 0, -1);
				insert(root[fa[x]], val[x] - v + lazy[fa[x]], 0, 1);
			}
			val[x] -= v;
		}
		else
		{
			int x;
			scanf("%d", &x);
			int ans = query(root[x]);
			if(fa[x] != 0)
			{
				int fans = val[fa[x]];
				if(fa[fa[x]] != 0)
				{
					fans += lazy[fa[fa[x]]];
				}
				ans ^= fans;
			}
			printf("%d\n", ans);
		}
	}
	return 0;
}