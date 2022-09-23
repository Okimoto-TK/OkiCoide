#include <cstdio>
#include <cstring>
#define int long long
const int mod = 1e9 + 7;
struct Matrix
{
	int n, m;
	long long a[105][105];
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
		for(int i = 0; i < _n; i++)
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
					(r.a[i][j] += a[i][k] * x.a[k][j] % mod) %= mod;
				}
			}
		}
		return r;
	}
};
int n, k;
Matrix op, re;
long long a[105];
Matrix power(Matrix x, int k)
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
signed main()
{
	scanf("%lld%lld", &n, &k);
	for(int i = 1; i <= n; i++)
	{
		scanf("%lld", &a[i]);
	}
	op.n = op.m = re.n = n;
	re.m = 1;
	for(int i = 1; i <= n; i++)
	{
		for(int j = 1; j <= n; j++)
		{
			//printf("%lld %lld %d\n", a[i], a[j], __builtin_popcountll(a[i] ^ a[j]));
			if(__builtin_popcountll(a[i] ^ a[j]) % 3 == 0)
			{
				op.a[i - 1][j - 1] = 1;
			}
		}
		re.a[i - 1][0] = 1;
	}
	re = power(op, k - 1) * re;
	long long ans = 0;
	for(int i = 1; i <= n; i++)
	{
		(ans += re.a[i - 1][0]) %= mod;
	}
	printf("%lld", ans);
	return 0;
}
