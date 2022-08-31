#include <cstdio>
#include <cstring>
const int mod = 1000;
struct Matrix
{
	int n, m;
	int a[10][10];
	Matrix()
	{
		memset(a, 0, sizeof(a));
	}
	Matrix(int x)
	{
		memset(a, 0, sizeof(a));
		for(int i = 1; i <= 8; i++)
		{
			for(int j = 1; j <= 8; j++)
			{
				a[i][j] = x;
			}
		}
	}
	Matrix operator*(const Matrix & A) const
	{
		Matrix R;
		R.n = n;
		R.m = A.m;
		for(int k = 1; k <= m; k++)
		{
			for(int i = 1; i <= n; i++)
			{
				if(a[i][k] == 0) continue;
				for(int j = 1; j <= A.m; j++)
				{
					(R.a[i][j] += a[i][k] * A.a[k][j] % mod) %= mod;
				}
			}
		}
		return R;
	}
};
Matrix M;
int pre(int x)
{
	return (x - 1 == 0) ? 8 : (x - 1);
}
int nxt(int x)
{
	return x == 8 ? 1 : (x + 1);
}
Matrix qpow(Matrix X, int k)
{
	Matrix R = X;
	k--;
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
int n;
int main()
{
	M.n = M.m = 8;
	for(int i = 1; i <= 8; i++)
	{
		if(i == 5) continue;
		M.a[i][pre(i)] = 1;
		M.a[i][nxt(i)] = 1;
	}
	scanf("%d", &n);
	Matrix R = qpow(M, n);
	printf("%d", R.a[1][5]);
	return 0;
}