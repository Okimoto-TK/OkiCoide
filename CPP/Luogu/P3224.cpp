#include <cstdio>
#include <algorithm>
#define N 100000
int n, m, q, pool;
int p[N + 5];
int s[N + 5];
int size[N + 5];
struct node
{
	int l, r, cnt, val;
} t[N * 50];
int root[N + 5];
void build(int i, int & k, int l, int r)
{
	if(k == 0)
	{
		k = ++pool;
	}
	if(l == r)
	{
		t[k].cnt++;
		t[k].val = i;
		return;
	}
	int mid = (l + r) >> 1;
	if(p[i] <= mid)
	{
		build(i, t[k].l, l, mid);
	}
	else
	{
		build(i, t[k].r, mid + 1, r);
	}
	t[k].cnt = t[t[k].l].cnt + t[t[k].r].cnt;
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
		t[k].cnt += t[_k].cnt;
		t[k].val += t[_k].val;
		return;
	}
	int mid = (l + r) >> 1;
	merge(t[k].l, t[_k].l, l, mid);
	merge(t[k].r, t[_k].r, mid + 1, r);
	t[k].cnt = t[t[k].l].cnt + t[t[k].r].cnt;
}
int query(int k, int l, int r, int x)
{
	if(t[k].cnt < x) return -1;
	if(l == r)
	{
		return t[k].val;
	}
	int mid = (l + r) >> 1;
	if(t[t[k].l].cnt >= x)
	{
		return query(t[k].l, l, mid, x);
	}
	else
	{
		return query(t[k].r, mid + 1, r, x - t[t[k].l].cnt);
	}
}
int find(int x)
{
	if(s[x] == x)
	{
		return x;
	}
	return s[x] = find(s[x]);
}
void merge(int x, int y)
{
	int fx = find(x);
	int fy = find(y);
	if(fx == fy) return;
	if(size[fx] < size[fy])
	{
		std::swap(x, y);
		std::swap(fx, fy);
	}
	merge(root[fx], root[fy], 1, N);
	s[fy] = fx;
	size[fx] += size[fy];
}
int query(int x, int y)
{
	return query(root[find(x)], 1, N, y);
}
int main()
{
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++)
	{
		scanf("%d", &p[i]);
		build(i, root[i], 1, N);
		s[i] = i;
	}
	for(int i = 1; i <= m; i++)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		merge(u, v);
	}
	scanf("%d", &q);
	for(int i = 1; i <= q; i++)
	{
		char op[2];
		scanf("%s", op);
		if(op[0] == 'B')
		{
			int x, y;
			scanf("%d%d", &x, &y);
			merge(x, y);
		}
		else
		{
			int x, y;
			scanf("%d%d", &x, &y);
			printf("%d\n", query(x, y));
		}
	}
}
