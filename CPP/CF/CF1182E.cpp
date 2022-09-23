#include <cstdio>
#include <cstring>
#define int long long
const int mod = 1e9 + 7;
struct Matrix
{
	int n, m;
	long long a[5][5];
	Matrix()
	{
		n = m = 0;
		memset(a, 0, sizeof(a));
	}
	Matrix(int _n, int _m, int v)
	{
		n = _n;
		m = _m;
		memset(a, 0, sizeof(a));
		for(int i = 0; i < n; i++)
		{
			a[i][i] = v;
		}
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
				{
					(r.a[i][j] += a[i][k] * x.a[k][j] % (mod - 1)) %= (mod - 1);
				}
			}
		}
		return r;
	}
	void print()
	{
		for(int i = 0; i < n; i++)
		{
			for(int j = 0; j < m; j++)
			{
				printf("%lld ", a[i][j]);
			}
			printf("\n");
		}
	}
};
Matrix fop;
Matrix gop;
Matrix r;
long long n;
int f[4];
int c;
Matrix power(Matrix x, long long k)
{
	Matrix re(x.n, x.m, 1);
	while(k)
	{
		if(k&1)
		{
			re = x * re;
		}
		x = x * x;
		k >>= 1;
	}
	return re;
}
long long power(long long x, long long k)
{
	long long re = 1;
	while(k)
	{
		if(k&1)
		{
			(re *= x) %= mod;
		}
		(x *= x) %= mod;
		k >>= 1;
	}
	return re;
}
signed main()
{
	scanf("%lld", &n);
	for(int i = 1; i <= 3; i++)
	{
		scanf("%lld", &f[i]);
	}
	scanf("%lld", &c);
	fop.n = fop.m = 3;
	fop.a[0][0] = fop.a[0][1] = fop.a[0][2] = fop.a[1][0] = fop.a[2][1] = 1;
	long long ans = 1;
	r = Matrix(3, 1, 0);
	r.a[2][0] = 1;
	r = power(fop, n - 3) * r;
	//r.print();
	(ans *= power(f[1], r.a[0][0])) %= mod;
	//printf("%lld\n", ans);
	r = Matrix(3, 1, 0);
	r.a[1][0] = 1;
	r = power(fop, n - 3) * r;
	//r.print();
	(ans *= power(f[2], r.a[0][0])) %= mod;
	//printf("%lld\n", ans);
	r = Matrix(3, 1, 0);
	r.a[0][0] = 1;
	r = power(fop, n - 3) * r;
	//r.print();
	(ans *= power(f[3], r.a[0][0])) %= mod;
	//printf("%lld\n", ans);
	gop.n = gop.m = 5;
	gop.a[0][0] = gop.a[0][1] = gop.a[0][2] = gop.a[0][3] = gop.a[1][0] = gop.a[2][1] = gop.a[3][3] = gop.a[4][4] = 1;
	gop.a[0][4] = gop.a[3][4] = 2;
	r = Matrix(5, 1, 0);
	r.a[4][0] = 1;
	r = power(gop, n - 3) * r;
	(ans *= power(c, r.a[0][0])) %= mod;
	printf("%lld", ans);
	return 0;
}
