#include <cstdio>
#include <cstring>
#define N 50000
struct Bas
{
	int bas[32];
	Bas()
	{
		memset(bas, 0, sizeof(bas));
	}
	void insert(int x)
	{
		for(int d = 30; d >= 0; d--)
		{
			if(x & (1 << d))
			{
				if(bas[d] == 0)
				{
					bas[d] = x;
					break;
				}
				else
				{
					x ^= bas[d];
				}
			}
		}
	}
	void operator+=(const Bas & a)
	{
		for(int i = 0; i <= 30; i++)
		{
			insert(a.bas[i]);
		}
	}
	int getMax()
	{
		int r = 0;
		for(int d = 30; d >= 0; d--)
		{
			if((r ^ bas[d]) > r)
			{
				r ^= bas[d];
			}
		}
		return r;
	}
};
Bas t[(N << 2) + 5];
void insert(int k, int l, int r, int x, int v)
{
	t[k].insert(v);
	if(l == r)
	{
		return;
	}
	int mid = (l + r) >> 1;
	if(x <= mid) insert(k << 1, l, mid, x, v);
	else insert(k << 1 | 1, mid + 1, r, x, v);
}
Bas query(int k, int l, int r, int x, int y)
{
	if(x <= l && r <= y)
	{
		return t[k];
	}
	int mid = (l + r) >> 1;
	Bas re;
	if(x <= mid) re += query(k << 1, l, mid, x, y);
	if(y > mid) re += query(k << 1 | 1, mid + 1, r, x, y);
	return re;
}
int n, m;
int main()
{
	scanf("%d%d", &m, &n);
	for(int i = 1; i <= m; i++)
	{
		int op, x, y;
		scanf("%d%d%d", &op, &x, &y);
		if(op == 1)
		{
			insert(1, 1, n, x, y);
		}
		else
		{
			printf("%d\n", query(1, 1, n, x, y).getMax());
		}
	}
	return 0;
}