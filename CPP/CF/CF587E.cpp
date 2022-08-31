#include <cstdio>
#include <cstring>
#define N 200000
struct Bit
{
	int t[N + 5];
	int lowbit(int x)
	{
		return x & (-x);
	}
	void change(int x, int v)
	{
		for(int i = x; i <= N; i += lowbit(i))
		{
			t[i] ^= v;
		}
	}
	int query(int x)
	{
		int r = 0;
		for(int i = x; i > 0; i -= lowbit(i))
		{
			r ^= t[i];
		}
		return r;
	}
} BIT;
struct Bas
{
	int bas[32];
	int size;
	void reset()
	{
		size = 0;
		memset(bas, 0, sizeof(bas));
	}
	Bas()
	{
		reset();
	}
	void insert(int x)
	{
		for(int d = 31; d >= 0; d--)
		{
			if(x & (1 << d))
			{
				if(bas[d] == 0)
				{
					bas[d] = x;
					size++;
					return;
				}
				else
				{
					x ^= bas[d];
				}
			}
		}
	}
	Bas merge(Bas A) const
	{
		for(int d = 31; d >= 0; d--)
		{
			if(bas[d] != 0)
			{
				A.insert(bas[d]);
			}
		}
		return A;
	}
} t[(N << 2) + 5];
int n, m;
int a[N + 5];
int b[N + 5];
void build(int k, int l, int r)
{
	if(l == r)
	{
		t[k].insert(b[l]);
		return;
	}
	int mid = (l + r) >> 1;
	build(k << 1, l, mid);
	build(k << 1 | 1, mid + 1, r);
	t[k] = t[k << 1].merge(t[k << 1 | 1]);
}
void change(int k, int l, int r, int x, int v)
{
	if(l == r)
	{
		t[k].reset();
		b[l] ^= v;
		t[k].insert(b[l]);
		return;
	}
	int mid = (l + r) >> 1;
	if(x <= mid) change(k << 1, l, mid, x, v);
	else change(k << 1 | 1, mid + 1, r, x, v);
	t[k] = t[k << 1].merge(t[k << 1 | 1]);
}
Bas query(int k, int l, int r, int x, int y)
{
	if(x <= l && r <= y)
	{
		return t[k];
	}
	int mid = (l + r) >> 1;
	Bas R;
	if(x <= mid) R = R.merge(query(k << 1, l, mid, x, y));
	if(y > mid) R = R.merge(query(k << 1 | 1, mid + 1, r, x, y));
	return R;
}
long long power(long long x, int k)
{
	long long r = 1;
	while(k)
	{
		if(k&1)
		{
			r *= x;
		}
		x *= x;
		k >>= 1;
	}
	return r;
}
int main()
{
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++)
	{
		scanf("%d", &a[i]);
		b[i] = a[i] ^ a[i - 1];
		BIT.change(i, b[i]);
	}
	build(1, 1, n);
	for(int i = 1; i <= m; i++)
	{
		int opt, l, r;
		scanf("%d%d%d", &opt, &l, &r);
		if(opt == 1)
		{
			int v;
			scanf("%d", &v);
			BIT.change(l, v);
			change(1, 1, n, l, v);
			if(r + 1 <= n)
			{
				BIT.change(r + 1, v);
				change(1, 1, n, r + 1, v);
			}
		}
		else
		{
			Bas R;
			if(l + 1 <= r) R = query(1, 1, n, l + 1, r);
			R.insert(BIT.query(l));
			printf("%lld\n", power(2, R.size));
		}
	}
	return 0;
}