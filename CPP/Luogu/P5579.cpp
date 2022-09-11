#include <cstdio>
#include <algorithm>
#define int long long
#define N 500000
int n, m;
int a[N + 5];
long long t[N * 4 + 5];
long long s[N * 4 + 5];
long long lazy[N * 4 + 5];
long long tag[N * 4 + 5];
long long max[N * 4 + 5];
bool cmp(int a, int b)
{
	return a > b;
}
void push_up(int k)
{
	s[k] = s[k << 1] + s[k << 1 | 1];
	t[k] = t[k << 1] + t[k << 1 | 1];
	max[k] = std::max(max[k << 1], max[k << 1 | 1]);
}
void build(int k, int l, int r)
{
	max[k] = 0;
	tag[k] = -1;
	if(l == r)
	{
		t[k] = 0;
		s[k] = a[l];
		return;
	}
	int mid = (l + r) >> 1;
	build(k << 1, l, mid);
	build(k << 1 | 1, mid + 1, r);
	push_up(k);
}
void update(int k, int l, long long v)
{
	t[k] += s[k] * v;
	max[k] += 1ll * a[l] * v;
	lazy[k] += v;
}
void cover(int k, int l, int r, long long b)
{
	t[k] = (r - l + 1) * b;
	max[k] = b;
	lazy[k] = 0;
	tag[k] = b;
}
void push_down(int k, int l, int r)
{
	int mid = (l + r) >> 1;
	if(tag[k] != -1) cover(k << 1, l, mid, tag[k]);
	if(tag[k] != -1) cover(k << 1 | 1, mid + 1, r, tag[k]);
	if(lazy[k] != 0) update(k << 1, l, lazy[k]);
	if(lazy[k] != 0) update(k << 1 | 1, mid + 1, lazy[k]);
	lazy[k] = 0;
	tag[k] = -1;
}
void change(int k, int l, int r, int x, int y, long long v)
{
	if(x <= l && r <= y)
	{
		update(k, l, v);
		return;
	}
	push_down(k, l, r);
	int mid = (l + r) >> 1;
	if(x <= mid)
	{
		change(k << 1, l, mid, x, y, v);
	}
	if(y > mid)
	{
		change(k << 1 | 1, mid + 1, r, x, y, v);
	}
	push_up(k);
}
void modify(int k, int l, int r, int x, int y, long long b)
{
	if(x <= l && r <= y)
	{
		cover(k, l, r, b);
		return;
	}
	push_down(k, l, r);
	int mid = (l + r) >> 1;
	if(x <= mid)
	{
		modify(k << 1, l, mid, x, y, b);
	}
	if(y > mid)
	{
		modify(k << 1 | 1, mid + 1, r, x, y, b);
	}
	push_up(k);
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
	if(x <= mid)
	{
		re += query(k << 1, l, mid, x, y);
	}
	if(y > mid)
	{
		re += query(k << 1 | 1, mid + 1, r, x, y);
	}
	return re;
}
int find(int k, int l, int r, int b)
{
	if(l == r)
	{
		if(max[k] < b) return -1;
		return l;
	}
	push_down(k, l, r);
	int mid = (l + r) >> 1;
	if(max[k << 1 | 1] >= b) return find(k << 1 | 1, mid + 1, r, b);
	else if(max[k << 1] >= b) return find(k << 1, l, mid, b);
	else return -1;
}
signed main()
{
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++)
	{
		scanf("%lld", &a[i]);
	}
	std::sort(a + 1, a + 1 + n, cmp);
	build(1, 1, n);
	long long last = 0;
	for(int i = 1; i <= m; i++)
	{
		long long d, b;
		scanf("%lld%lld", &d, &b);
		change(1, 1, n, 1, n, d - last);
		long long ptr = find(1, 1, n, b);
		/*
		for(int j = 1; j <= n; j++)
		{
			printf("--%d %lld\n", j, query(1, 1, n, j, j));
		}
		*/
		if(ptr == -1)
		{
			printf("0\n");
		}
		else
		{
			printf("%lld\n", query(1, 1, n, 1, ptr) - ptr * b);
			modify(1, 1, n, 1, ptr, b);
		}
		/*
		for(int j = 1; j <= n; j++)
		{
			printf("--%d %lld\n", j, query(1, 1, n, j, j));
		}
		*/
		last = d;
	}
	return 0;
}