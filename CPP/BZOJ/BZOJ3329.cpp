#include <cstdio>
#include <cstring>
#define N 64
int maxdep;
long long f[N + 5][2][2];
int num[N + 5];
long long dfs(int dep, int chose, bool lim)
{
	if(dep < 0)
	{
		return 1;
	} 
	if(f[dep][chose][lim] >= 0)
	{
		return f[dep][chose][lim];
	}
	int maxval = lim ? num[dep] : 1;
	long long ans = 0;
	if(!chose && maxval == 1) ans += dfs(dep - 1, true, lim && 1 == maxval);
	ans += dfs(dep - 1, false, lim && 0 == maxval);
	return f[dep][chose][lim] = ans;
}
long long calc(long long n)
{
	long long x = n;
	maxdep = 0;
	while(x != 0)
	{
		num[maxdep++] = x % 2;
		x /= 2;
	}
	return dfs(--maxdep, false, true);
}
const int mod = 1e9 + 7;
struct Matrix
{
	long long a[2][2];
	int n, m;
	Matrix()
	{
		n = m = 0;
		memset(a, 0, sizeof(a));
	}
	Matrix(int _n, int _m, int v)
	{
		n = _n, m = _m;
		memset(a, 0, sizeof(a));
		a[0][0] = a[1][1] = v;
	}
	Matrix operator*(const Matrix & x)
	{
		Matrix r(n, x.m, 0);
		for(int k = 0; k < m; k++)
		{
			for(int i = 0; i < n; i++)
			{
				if(a[i][k] == 0) continue;
				for(int j = 0; j < x.m; j++)
				{
					(r.a[i][j] += a[i][k] * x.a[k][j] % mod) %= mod;
				}
			}
		}
		return r;
	}
};
Matrix power(Matrix x, long long k)
{
	Matrix r(x.n, x.m, 1);
	while(k)
	{
		if(k&1)
		{
			r = r * x;
		}
		x = x * x;
		k >>= 1;
	}
	return r;
}
Matrix op;
Matrix e;
long long n;
int main()
{
	int t;
	op.n = op.m = 2;
	e.n = 2, e.m = 1;
	op.a[0][0] = op.a[0][1] = op.a[1][0] = 1;
	e.a[0][0] = 1;
	for(scanf("%d", &t); t; t--)
	{
		memset(f, -1, sizeof(f));
		memset(num, 0, sizeof(num));
		scanf("%lld", &n);
		printf("%lld\n", calc(n) - 1);
		Matrix r = power(op, n) * e;
		printf("%lld\n", (r.a[0][0] + r.a[1][0]) % mod);
	}
}
