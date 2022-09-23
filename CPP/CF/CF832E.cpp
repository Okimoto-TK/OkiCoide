#include <cstdio>
#include <cstring>
struct num
{
	int a[505];
	num()
	{
		memset(a, 0, sizeof(a));
	}
	num operator^(const num & x) const
	{
		num r;
		for(int d = 500; d >= 0; d--)
		{
			r.a[d] = (a[d] + x.a[d]) % 5;
		}
		return r;
	}
	bool empty()
	{
		for(int d = 500; d >= 1; d--)
		{
			if(a[d]) return false;
		}
		return true;
	}
	void print()
	{
		for(int i = 1; i <= 2; i++)
		{
			printf("%d", a[i]);
		}
		printf("\n");
	}
};
struct Bas
{
	int siz;
	num b[505];
	void insert(num x)
	{
		for(int d = 500; d >= 0; d--)
		{
			if(x.a[d] != 0)
			{
				if(b[d].empty())
				{
					siz++;
					b[d] = x;
					break;
				}
				else
				{
					while(x.a[d] != 0)
					{
						x = x ^ b[d];
					}
				}
			}
		}
	}
	int count(num x)
	{
		int re = 0;
		for(int d = 500; d >= 1; d--)
		{
			if(x.a[d] != 0)
			{
				if(b[d].empty()) return -1;
				while(x.a[d] != 0)
				{
					x = x ^ b[d];
				}
				re++;
			}
		}
		return re;
	}
} bas;
int n, m;
char buf[505];
num a[505];
num t;
const int mod = 1e9 + 7;
long long power(long long x, int k)
{
	if(k < 0) return 0;
	long long r = 1;
	while(k)
	{
		if(k&1)
		{
			(r *= x) %= mod;
		}
		(x *= x) %= mod;
		k >>= 1;
	}
	return r;
}
int main()
{
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++)
	{
		scanf("%s", buf + 1);
		for(int j = 1; j <= m; j++)
		{
			a[i].a[j] = (buf[j] - 'a') % 5;
		}
		bas.insert(a[i]);
	}
	int q;
	scanf("%d", &q);
	for(int i = 1; i <= q; i++)
	{
		scanf("%s", buf + 1);
		for(int j = 1; j <= m; j++)
		{
			t.a[j] = (buf[j] - 'a') % 5;
		}
		if(bas.count(t) == -1)
		{
			printf("0\n");
			continue;
		}
		printf("%lld\n", power(5, n - bas.siz));
	}
	return 0;
}
