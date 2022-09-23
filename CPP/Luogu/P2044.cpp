#include <cstdio>
#include <cstring>
#define int long long
int mod;
long long time(long long x, long long y)
{
	int base = 0;
	unsigned long long re = 0; 
	while(y)
	{
		unsigned long long tmp = (y % 10) * x % mod;
		for(int i = 1; i <= base; i++)
		{
			(tmp *= 10) %= mod;
		}
		base++;
		re += tmp;
		y /= 10;
	}
	return re;
}
struct Matrix
{
	int n, m;
	long long a[2][2];
	Matrix()
	{
		memset(a, 0, sizeof(a));
		n = m = 0;
	}
	Matrix(int _n, int _m, int v)
	{
		n = _n;
		m = _m;
		for(int i = 0; i < n; i++)
		{
			for(int j = 0; j < m; j++)
			{
				a[i][j] = 0;
			}
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
					(r.a[i][j] += time(a[i][k], x.a[k][j]) % mod) %= mod;
				}
			}
		}
		return r;
	}
};
Matrix A, B;
int a, c, x0, n, g;
Matrix qpow(Matrix x, int k)
{
	Matrix r(x.n, x.m, 1);
	while(k)
	{
		if(k&1) r = r * x;
		x = x * x;
		k >>= 1;
	}
	return r;
}
signed main()
{
	scanf("%lld%lld%lld%lld%lld%lld", &mod, &a, &c, &x0, &n, &g);
	A.n = A.m = 2;
	A.a[0][0] = a, A.a[0][1] = c, A.a[1][1] = 1;
	B.n = 2;
	B.m = 1;
	B.a[0][0] = x0;
	B.a[1][0] = 1;
	B = qpow(A, n) * B;
	printf("%lld", B.a[0][0] % mod % g);
	return 0;	
}
