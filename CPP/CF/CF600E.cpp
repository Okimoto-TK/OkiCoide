#include <cstdio>
#include <vector>
#define N 100000
struct node
{
	int lc, rc;
	int max;
	long long sum;
	node()
	{
		lc = rc = 0;
		max = sum = 0;
	}
} t[5000000];
int n, pool;
int col[N + 5];
long long ans[N + 5];
int root[N + 5];
std::vector<int> vec[N + 5];
void merge(const node & a, const node & b, node & r)
{
	if(a.max > b.max)
	{
		r.max = a.max;
		r.sum = a.sum;
	}
	else if(b.max > a.max)
	{
		r.max = b.max;
		r.sum = b.sum;
	}
	else
	{
		r.max = a.max;
		r.sum = a.sum + b.sum;
	}
}
void insert(int & k, int l, int r, int x)
{
	if(k == 0) k = ++pool;
	if(l == r)
	{
		t[k].sum = x;
		t[k].max = 1;
		return;
	}
	int mid = (l + r) >> 1;
	if(x <= mid) insert(t[k].lc, l, mid, x);
	else insert(t[k].rc, mid + 1, r, x);
	merge(t[t[k].lc], t[t[k].rc], t[k]);
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
		t[k].max += t[_k].max;
		return;
	}
	int mid = (l + r) >> 1;
	merge(t[k].lc, t[_k].lc, l, mid);
	merge(t[k].rc, t[_k].rc, mid + 1, r);
	merge(t[t[k].lc], t[t[k].rc], t[k]);
}
void dfs(int u, int fa)
{
	for(auto v : vec[u])
	{
		if(v == fa) continue;
		dfs(v, u);
		merge(root[u], root[v], 1, n);
	}
	ans[u] = t[root[u]].sum;
}
int main()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
	{
		scanf("%d", &col[i]);
		insert(root[i], 1, n, col[i]);
	}
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
		printf("%lld ", ans[i]);
	}
	return 0;
}
