#include <cstdio>
#include <vector>
#include <set>
#define N 100000
int n, q, pool;

int dfn[N + 5];
int rpr[N + 5];
int siz[N + 5];
std::vector<int> vec[N + 5];
std::set<int> col[N + 5];
void dfs(int u, int fa)
{
	dfn[u] = ++pool;
	rpr[pool] = u;
	siz[u] = 1;
	for(auto v : vec[u])
	{
		if(v == fa) continue;
		dfs(v, u);
		siz[u] += siz[v];
	}
}
long long t[N * 4 + 5];
long long lazy[N * 4 + 5];
void update(int k, int l, int r, int v)
{
	t[k] += 1ll * (r - l + 1) * v;
	lazy[k] += v;
}
void push_down(int k, int l, int r)
{
	if(lazy[k] == 0) return;
	int mid = (l + r) >> 1;
	update(k << 1, l, mid, lazy[k]);
	update(k << 1 | 1, mid + 1, r, lazy[k]);
	lazy[k] = 0;
}
void change(int k, int l, int r, int x, int y, int v)
{
	if(x <= l && r <= y)
	{
		update(k, l, r, v);
		return;
	}
	int mid = (l + r) >> 1;
	push_down(k, l, r);
	if(x <= mid) change(k << 1, l, mid, x, y, v);
	if(y > mid) change(k << 1 | 1, mid + 1, r, x, y, v);
	t[k] = t[k << 1] + t[k << 1 | 1];
}
long long query(int k, int l, int r, int x, int y)
{
	if(x <= l && r <= y)
	{
		return t[k];
	}
	push_down(k, l, r);
	int mid = (l + r) >> 1;
	long long re = 0;
	if(x <= mid) re += query(k << 1, l, mid, x, y);
	if(y > mid) re += query(k << 1 | 1, mid + 1, r, x, y);
	return re;
}
inline int L(int x)
{
	return dfn[x];
}
inline int R(int x)
{
	return dfn[x] + siz[x] - 1;
}
int main()
{
	scanf("%d%d", &n, &q);
	for(int i = 1; i < n; i++)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		vec[u].push_back(v);
		vec[v].push_back(u);
	}
	dfs(1, 0);
	for(int i = 1; i <= q; i++)
	{
		int opt;
		scanf("%d", &opt);
		if(opt == 1)
		{
			int x, c;
			scanf("%d%d", &x, &c);
			int l = L(x);
			int r = R(x);
			auto it = col[c].lower_bound(l);
			if(it != col[c].begin())
			{
				it--;
				if(*it <= dfn[x] && *it + siz[rpr[*it]] - 1 >= dfn[x]) continue;
				it++;
			}
			bool fail = true;
			for(; it != col[c].end() && *it <= r; it++)
			{
				fail = false;
				change(1, 1, n, *it, *it + siz[rpr[*it]] - 1, -1);
			}
			if(!fail) col[c].erase(col[c].lower_bound(l), col[c].upper_bound(r));
			col[c].insert(dfn[x]);
			change(1, 1, n, dfn[x], dfn[x] + siz[x] - 1, 1);
			//printf("%d %d\n", dfn[x], dfn[x] + siz[x] - 1);
		}
		else
		{
			int x;
			scanf("%d", &x);
			printf("%lld\n", query(1, 1, n, dfn[x], dfn[x] + siz[x] - 1));
			//printf("%d %d\n", dfn[x], dfn[x] + siz[x] - 1);
		}
	}
	return 0;
}