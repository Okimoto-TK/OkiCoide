#include <cstdio>
#include <cstring>
const int mod = 1e9 + 7;
struct Matrix
{
	int n, m;
	long long a[2][2];
	Matrix()
	{
		a[0][0] = a[0][1] = a[1][0] = a[1][1] = 0;
		n = m = 0;
	}
	Matrix(int x)
	{
		a[0][1] = a[1][0] = 0;
		a[0][0] = a[1][1] = x;
	}
	Matrix operator*(const Matrix & A) const
	{
		Matrix R;
		R.n = n;
		R.m = A.m;
		for(int k = 0; k < m; k++)
		{
			for(int i = 0; i < n; i++)
			{
				if(a[i][k] == 0) continue;
				for(int j = 0; j < A.m; j++)
				{
					(R.a[i][j] += a[i][k] * A.a[k][j] % mod) %= mod;
				}
			}
		}
		return R;
	}
};
Matrix M, N, E;
char n[1000005], m[1000005];
char _n[1000005], _m[1000005];
int a, b, c, d;
Matrix power(Matrix X, int k)
{
	Matrix R = Matrix(1);
	R.n = R.m = X.n;
	while(k)
	{
		if(k&1)
		{
			R = R * X;
		}
		X = X * X;
		k >>= 1;
	}
	return R;
}
Matrix qpow(Matrix X, char k[1000005])
{
	Matrix R = Matrix(1);
	R.n = R.m = X.n;
	int len = strlen(k);
	for(int i = len - 1; i >= 0; i--)
	{
		R = R * (power(X, int(k[i] - '0')));
		X = power(X, 10);
	}
	return R;
}
int main()
{
	scanf("%s%s%d%d%d%d", n, m, &a, &b, &c, &d);
	int len = strlen(n);
	memcpy(_m, m, sizeof(m));
	memcpy(_n, n, sizeof(n));
	for(int i = len - 1; i >= 0; i--)
	{
		_n[i]--;
		if(_n[i] < '0') _n[i] = '9';
		else
		{
			break;
		}
	}
	len = strlen(m);
	for(int i = len - 1; i >= 0; i--)
	{
		_m[i]--;
		if(_m[i] < '0') _m[i] = '9';
		else
		{
			break;
		}
	}
	M.n = M.m = N.n = N.m = 2;
	M.a[0][0] = a;
	M.a[0][1] = b;
	M.a[1][1] = 1;
	N.a[0][0] = c;
	N.a[0][1] = d;
	N.a[1][1] = 1;
	E.n = 2;
	E.m = 1;
	E.a[0][0] = E.a[1][0] = 1;
	M = qpow(M, _m);
	N = M * N;
	N = qpow(N, _n);
	Matrix ANS = (N * M) * E;
	printf("%lld\n", ANS.a[0][0]);
	return 0;
}