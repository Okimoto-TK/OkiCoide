#include <cstdio>
#include <algorithm>
#define N 2000000
int n, k;
int lmax[N * 4 + 5];
int lmin[N * 4 + 5];
void build(int k, int l, int r)
{
	lmax[k] = 0;
	lmin[k] = 0x3f3f3f3f;
	if(l == r) return;
	int mid = (l + r) >> 1;
	build(k << 1, l, mid);
	build(k << 1 | 1, mid + 1, r);
}
void updmax(int k, int v)
{
	if(v > lmax[k])
	{
		lmax[k] = v;
	}
	if(v > lmin[k])
	{
		lmin[k] = v;
	}
}
void updmin(int k, int v)
{
	if(v < lmin[k])
	{
		lmin[k] = v;
	}
	if(v < lmax[k])
	{
		lmax[k] = v;
	}
}
void push_down(int k)
{
	updmax(k << 1, lmax[k]);
	updmin(k << 1, lmin[k]);
	updmax(k << 1 | 1, lmax[k]);
	updmin(k << 1 | 1, lmin[k]);
	lmax[k] = 0;
	lmin[k] = 0x3f3f3f3f;
}
void change(int k, int l, int r, int x, int y, int typ, int v)
{
	if(x <= l && r <= y)
	{
		if(typ == 1)
		{
			updmax(k, v);
		}
		else
		{
			updmin(k, v);
		}
		return;
	}
	push_down(k);
	int mid = (l + r) >> 1;
	if(x <= mid) change(k << 1, l, mid, x, y, typ, v);
	if(y > mid) change(k << 1 | 1, mid + 1, r, x, y, typ, v);
}
void dfs(int k, int l, int r, int max, int min)
{
	min = std::min(min, lmin[k]);
	max = std::max(max, lmax[k]);
	if(l == r)
	{
		printf("%d\n", max);
		return;
	}
	push_down(k);
	int mid = (l + r) >> 1;
	dfs(k << 1, l, mid, max, min);
	dfs(k << 1 | 1, mid + 1, r, max, min);
}
int main()
{
	scanf("%d%d", &n, &k);
	build(1, 1, n);
	for(int i = 1; i <= k; i++)
	{
		int t, l, r, h;
		scanf("%d%d%d%d", &t, &l, &r, &h);
		l++;
		r++;
		change(1, 1, n, l, r, t, h);
	}
	dfs(1, 1, n, 0, 0x3f3f3f3f);
	return 0;
}