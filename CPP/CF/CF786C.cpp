#include <cstdio>
struct node
{
	int val;
	int lc, rc;
} t[10000000];
int root[100005];
int last[100005];
int n, pool;
void build(int & k, int l, int r)
{
	k = ++pool;
	if(l == r)
	{
		return;
	}
	int mid = (l + r) >> 1;
	build(t[k].lc, l, mid);
	build(t[k].rc, mid + 1, r);
}
void insert(int & k, int l, int r, int x, int v)
{
	t[++pool] = t[k];
	k = pool; 
	if(l == r)
	{
		t[k].val = v;
		return;
	}
	int mid = (l + r) >> 1;
	if(x <= mid)
	{
		insert(t[k].lc, l, mid, x, v);
	}
	else
	{
		insert(t[k].rc, mid + 1, r, x, v);
	}
	t[k].val = t[t[k].lc].val + t[t[k].rc].val;
}
int query(int k, int l, int r, int max)
{
	if(l == r)
	{
		if(max < t[k].val)
		{
			return l + 1;
		}
		return l;
	}
	int mid = (l + r) >> 1;
	if(t[t[k].rc].val <= max)
	{
		return query(t[k].lc, l, mid, max - t[t[k].rc].val);
	}
	else
	{
		return query(t[k].rc, mid + 1, r, max);
	}
}
int main()
{
	scanf("%d", &n);
	build(root[0], 1, n);
	for(int i = 1; i <= n; i++)
	{
		root[i] = root[i - 1];
		int a;
		scanf("%d", &a);
		if(last[a] != 0)
		{
			insert(root[i], 1, n, last[a], 0);
		}
		insert(root[i], 1, n, i, 1);
		last[a] = i;
	}
	for(int k = 1; k <= n; k++)
	{
		int ans = 0;
		int now = n;
		while(now >= 1)
		{	
			now = query(root[now], 1, n, k) - 1;
			//printf("--%d\n", now);
			ans++;
		}
		printf("%d\n", ans);
	}
	return 0;
}
