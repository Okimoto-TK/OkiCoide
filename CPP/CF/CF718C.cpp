#include <cstdio>
#include <cstring>
#define int long long
#define N 100000
const int mod = 1e9 + 7;
struct Matrix
{
	int n, m;
	int a[2][2];
	Matrix()
	{
		n = m = 0;
		memset(a, 0, sizeof(a));
	}
	Matrix(int _n, int _m, int v)
	{
		n = _n, m = _m;
		a[0][1] = a[1][0] = 0;
		a[1][1] = a[0][0] = v;
	}
	Matrix operator*(const Matrix & x) const
	{
		Matrix r(n, x.m, 0);
		for(int k = 0; k < m; k++)
		{
			for(int i = 0; i < n; i++)
			{
				if(a[i][k] == 0) continue;
				for(int j = 0; j < x.m; j++)
				(r.a[i][j] += a[i][k] * x.a[k][j] % mod) %= mod;
			}
		}
		return r;
	}
	Matrix operator+(const Matrix & x) const
	{
		Matrix r(n, m, 0);
		for(int i = 0; i < n; i++)
		{
			for(int j = 0; j < m; j++)
			{
				r.a[i][j] = (a[i][j] + x.a[i][j]) % mod;
			}
		}
		return r;
	}
	bool empty()
	{
		return a[0][0] == 1 && a[1][1] == 1 && a[0][1] == 0 && a[1][0] == 1;
	}
};
int n, m;
Matrix op(2, 2, 0);
Matrix e(2, 1, 1);
int a[N + 5];
Matrix t[N * 4 + 5];
Matrix lazy[N * 4 + 5];
Matrix power(Matrix x, int k)
{
	Matrix r(x.n, x.m, 1);
	while(k)
	{
		if(k & 1)
		{
			r = r * x;
		}
		x = x * x;
		k >>= 1;
	}
	return r;
}
void build(int k, int l, int r)
{
	lazy[k] = Matrix(2, 2, 1);
	if(l == r)
	{
		t[k] = power(op, a[l] - 1) * e;
		return;
	}
	int mid = (l + r) >> 1;
	build(k << 1, l, mid);
	build(k << 1| 1, mid + 1, r);
	t[k] = t[k << 1] + t[k << 1 | 1];
}
void update(int k, const Matrix & v)
{
	t[k] = v * t[k];
	lazy[k] = v * lazy[k];
}
void push_down(int k)
{
	if(lazy[k].empty()) return;
	update(k << 1, lazy[k]);
	update(k << 1 | 1, lazy[k]);
	lazy[k] = Matrix(2, 2, 1);
}
void change(int k, int l, int r, int x, int y, const Matrix & v)
{
	if(x <= l && r <= y)
	{
		update(k, v);
		return;
	}
	push_down(k);
	int mid = (l + r) >> 1;
	if(x <= mid) change(k << 1, l, mid, x, y, v);
	if(y > mid) change(k << 1 | 1, mid + 1, r, x, y, v);
	t[k] = t[k << 1] + t[k << 1 | 1];
}
long long query(int k, int l, int r, int x, int y)
{
	if(x <= l && r <= y)
	{
		return t[k].a[0][0];
	}
	push_down(k);
	int mid = (l + r) >> 1;
	long long re = 0;
	if(x <= mid) (re += query(k << 1, l, mid, x, y)) %= mod;
	if(y > mid) (re += query(k << 1 | 1, mid + 1, r, x, y)) %= mod;
	return re;
}
signed main()
{
	op.a[0][0] = op.a[0][1] = op.a[1][0] = 1;
	scanf("%lld%lld", &n, &m);
	for(int i = 1; i <= n; i++)
	{
		scanf("%lld", &a[i]);
	}
	build(1, 1, n);
	for(int i = 1; i <= m; i++)
	{
		int opt;
		scanf("%lld", &opt);
		if(opt == 1)
		{
			int l, r, x;
			scanf("%lld%lld%lld", &l, &r, &x);
			Matrix tmp = power(op, x);
			change(1, 1, n, l, r, tmp);
		}
		else if(opt == 2)
		{
			int l, r;
			scanf("%lld%lld", &l, &r);
			printf("%lld\n", query(1, 1, n, l, r));
		}
	}
	return 0;
}
