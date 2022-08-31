#include <cstdio>
#include <cstring>
#define N 50000
struct Bas
{
	int bas[32];
	void reset()
	{
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
					return;
				}
				else
				{
					x ^= bas[d];
				}
			}
		}
	}
	int query(int x)
	{
		for(int d = 31; d >= 0; d--)
		{
			if((x ^ bas[d]) > x)
			{
				x ^= bas[d];
			}
		}
		return x;
	}
	Bas merge(const Bas & A) const
	{
		Bas B = A;
		for(int d = 31; d >= 0; d--)
		{
			if(bas[d] != 0)
			{
				B.insert(bas[d]);
			}
		}
		return B;
	}
} t[(N << 2) + 5];
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
		int ans = 0;
		for(int i = x; i > 0; i -= lowbit(i))
		{
			ans ^= t[i];
		}
		return ans;
	}
} BIT;
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
		int opt, l, r, v;
		scanf("%d%d%d%d", &opt, &l, &r, &v);
		if(opt == 1)
		{
			BIT.change(l, v);
			if(r + 1 <= n) BIT.change(r + 1, v);
			change(1, 1, n, l, v);
			if(r + 1 <= n) change(1, 1, n, r + 1, v);
		}
		else
		{
			Bas R = query(1, 1, n, l + 1, r);
			R.insert(BIT.query(l));
			printf("%d\n", R.query(v));
		}
	}
	return 0;
}