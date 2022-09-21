#include <cstdio>
#define N 500000
int n;
int a[N + 5];
struct Bas
{
	int b[20];
	int last[20];
	void insert(int x, int id)
	{
		for(int d = 19; d >= 0; d--)
		{
			if(x & (1 << d))
			{
				if(id > last[d])
				{
					int tmp = b[d];
					int tmp2 = last[d];
					b[d] = x;
					last[d] = id;
					x = tmp ^ b[d];
					id = tmp2;
				}
				else
				{
					x ^= b[d];
				}
			}
		}
	}
	int getMax(int x, int l)
	{
		for(int d = 19; d >= 0; d--)
		{
			if(last[d] >= l && (b[d] ^ x) > x)
			{
				x ^= b[d];
			}
		}
		return x;
	}
} v[N + 5];
int main()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
	{
		scanf("%d", &a[i]);
	}
	for(int i = 1; i <= n; i++)
	{
		v[i] = v[i - 1];
		v[i].insert(a[i], i);
	}
	int q;
	scanf("%d", &q);
	for(int i = 1; i <= q; i++)
	{
		int l, r;
		scanf("%d%d", &l, &r);
		printf("%d\n", v[r].getMax(0, l));
	}
	return 0;
} 
