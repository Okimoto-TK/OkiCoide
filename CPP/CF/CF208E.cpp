#include <cstdio>
#include <vector>
#include <algorithm>
#define N 100005
int n, cnt, m;
std::vector<int> vec[N + 5];
std::vector<int> dev[N + 5];
int anc[N + 5][20];
int dep[N + 5];
int son[N + 5];
int siz[N + 5];
int seg[N + 5];
int rpr[N + 5];
int top[N + 5];
int t[N * 4 + 5];
int _t[N * 4 + 5];
int ans[N + 5];
struct query
{
	int u, p, id;
} q[N + 5];
bool cmp(query a, query b)
{
	return dep[a.u] < dep[b.u];
}
void dfs1(int u, int f)
{
	dep[u] = dep[f] + 1;
	dev[dep[u]].push_back(u);
	anc[u][0] = f;
	siz[u] = 1;
	for(int i = 1; i <= 18; i++)
	{
		anc[u][i] = anc[anc[u][i - 1]][i - 1];
	}
	for(auto v : vec[u])
	{
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
		int v = son[u];
		seg[v] = ++seg[0];
		rpr[seg[0]] = v;
		top[v] = top[u];
		dfs2(v);
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
void push_down(int * ar, int k)
{
	if(ar[k] != 0)
	{
		ar[k << 1] += ar[k];
		ar[k << 1 | 1] += ar[k];
		ar[k] = 0;
	}
}
void change(int * ar, int k, int l, int r, int x, int y, int v)
{
	if(x <= l && r <= y)
	{
		ar[k] += v;
		return;
	}
	push_down(ar, k);
	int mid = (l + r) >> 1;
	if(x <= mid)
	{
		change(ar, k << 1, l, mid, x, y, v);
	}
	if(y > mid)
	{
		change(ar, k << 1 | 1, mid + 1, r, x, y, v);
	}
}
int query(int * ar, int k, int l, int r, int x)
{
	if(l == r)
	{
		return ar[k];
	}
	push_down(ar, k);
	int mid = (l + r) >> 1;
	if(x <= mid)
	{
		return query(ar, k << 1, l, mid, x);
	}
	else
	{
		return query(ar, k << 1 | 1, mid + 1, r, x);
	}
}
void modify(int * ar, int x, int y, int v)
{
	int fx = top[x];
	int fy = top[y];
	while(fx != fy)
	{
		if(dep[fx] < dep[fy])
		{
			std::swap(x, y);
			std::swap(fx, fy);
		}
		change(ar, 1, 1, seg[0], seg[fx], seg[x], v);
		x = anc[fx][0];
		fx = top[x];
	}
	if(dep[x] > dep[y])
	{
		std::swap(x, y);
	}
	change(ar, 1, 1, seg[0], seg[x], seg[y], v);
}
void update(int d)
{
	for(auto u : dev[d - 1])
	{
		modify(_t, 1, u, 1);
	}
	for(auto u : dev[d])
	{
		modify(t, 1, u, 1);
	}
}
int kanc(int u, int k)
{
	for(int i = 18; i >= 0; i--)
	{
		if((1 << i) & k)
		{
			u = anc[u][i];
		}
	}
	return u;
}
int ask(int u, int p)
{
	int c = kanc(u, p);
	if(c == 1 || c == 0) return 0;
	//printf("%d %d %d\n", query(t, 1, 1, seg[0], c), query(_t, 1, 1, seg[0], c), query(t, 1, 1, seg[0], c) - query(_t, 1, 1, seg[0], c) - 1);
	return query(t, 1, 1, seg[0], seg[c]) - query(_t, 1, 1, seg[0], seg[c]) - 1;
}
int main()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
	{
		int r;
		scanf("%d", &r);
		r++;
		vec[r].push_back(i + 1);
	}
	dfs1(1, 0);
	seg[0] = seg[1] = rpr[1] = top[1] = 1;
	dfs2(1);
	scanf("%d", &m);
	for(int i = 1; i <= m; i++)
	{
		scanf("%d%d", &q[i].u, &q[i].p);
		q[i].id = i;
		q[i].u++;
	}
	std::sort(q + 1, q + 1 + m, cmp);
	int now = 0;
	for(int i = 1; i <= m; i++)
	{
		//printf("%d\n", dep[q[i].u]);
		while(now < dep[q[i].u])
		{
			update(++now);
		}
		ans[q[i].id] = ask(q[i].u, q[i].p);
	}
	for(int i = 1; i <= m; i++)
	{
		printf("%d ", ans[i]);
	}
	return 0;
}