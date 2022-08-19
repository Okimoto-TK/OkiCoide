#include <cstdio>
#include <queue>
#define N 100005
#define HN 50001
#define int long long
int p, pool;
int n, m;
struct drawf
{
	int l, r, val, lazy;
	drawf()
	{
		l = r = val = lazy = 0;
	}
} d[15000000];
void update(int & k, int l, int r, int v)
{
	if(k == 0) k = ++p;
	d[k].val += (r - l + 1) * v;
	d[k].lazy += v;
}
void push_down(int k, int l, int r)
{
	if(d[k].lazy != 0)
	{
		int mid = (l + r) >> 1;
		update(d[k].l, l, mid, d[k].lazy);
		update(d[k].r, mid + 1, r, d[k].lazy);
		d[k].lazy = 0;
	}
}
void change(int & k, int l, int r, int x, int y, int v)
{
	if(k == 0) k = ++p;
	if(x <= l && r <= y)
	{
		update(k, l, r, v);
		return;
	}
	push_down(k, l, r);
	int mid = (l + r) >> 1;
	if(x <= mid) change(d[k].l, l, mid, x, y, v);
	if(y > mid) change(d[k].r, mid + 1, r, x, y, v);
	d[k].val = d[d[k].l].val + d[d[k].r].val;
}
long long ask(int k, int l, int r, int x, int y)
{
	if(k == 0) return 0;
	if(x <= l && r <= y)
	{
		return d[k].val;
	}
	push_down(k, l, r);
	int mid = (l + r) >> 1;
	long long re = 0;
	if(x <= mid) re += ask(d[k].l, l, mid, x, y);
	if(y > mid) re += ask(d[k].r, mid + 1, r, x, y);
	return re;
}
int t[400010];
void modify(int k, int l, int r, int x, int L, int R)
{
	if(l == r)
	{
		change(t[k], 1, n, L, R, 1);
		return;
	}
	int mid = (l + r) >> 1;
	if(x <= mid) modify(k << 1, l, mid, x, L, R);
	else modify(k << 1 | 1, mid + 1, r, x, L, R);
	change(t[k], 1, n, L, R, 1);
}
long long query(int k, int l, int r, int x, int y, int L, int R)
{
	if(x <= l && r <= y)
	{
		return ask(t[k], 1, n, L, R);
	}
	int mid = (l + r) >> 1;
	long long re = 0;
	if(x <= mid) re += query(k << 1, l, mid, x, y, L, R);
	if(y > mid) re += query(k << 1 | 1, mid + 1, r, x, y, L, R);
	return re;
}
bool check(int x, int l, int r, long long c)
{
	//printf("%d %d\n", x, query(1, 1, N, x, N, l, r));
	return query(1, 1, N, x, N, l, r) >= c;
}
int half(int x, int y, long long c)
{
	int l = 1, r = N;
	while(l < r)
	{
		int mid = (l + r + 1) >> 1;
		if(check(mid, x, y, c))
		{
			l = mid;
		}
		else
		{
			r = mid - 1;
		}
	}
	return l - HN;
}
signed main()
{
	scanf("%lld%lld", &n, &m);
	for(int i = 1; i <= m; i++)
	{
		int op, l, r;
		long long c;
		scanf("%lld%lld%lld%lld", &op, &l, &r, &c);
		if(op == 1)
		{
			c += HN;
			modify(1, 1, N, (int)c, l, r);
		}
		else
		{
			printf("%d\n", half(l, r, c));
		}
	}
	return 0;
}