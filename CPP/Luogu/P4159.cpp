#include <cstdio>
const int mod = 2009;
struct Matrix
{
	int n, m;
	int a[105][105];
	Matrix()
	{
		for(int i = 0; i <= 100; i++)
		{
			for(int j = 0; j <= 100; j++)
			{
				a[i][j] = 0;
			}
		}
	}
	Matrix(int x)
	{
		for(int i = 0; i <= 100; i++)
		{
			for(int j = 0; j <= 100; j++)
			{
				a[i][j] = 0;
			}
			a[i][i] = x;
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
				for(int j = 1; j <= A.m ; j++)
				{
					(R.a[i][j] += a[i][k] * A.a[k][j] % mod) %= mod;
				}
			}
		}
		return R;
	}
};
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
int n, t;
Matrix M, N;
int main()
{
	scanf("%d%d", &n, &t);
	M.n = M.m = N.n = 9 * n;
	N.m = 1;
	for(int i = 1; i <= n; i++)
	{
		for(int j = 2; j <= 9; j++)
		{
			M.a[(i - 1) * 9 + j][(i - 1) * 9 + j - 1] = 1;
		}
	}
	for(int i = 1; i <= n; i++)
	{
		for(int j = 1; j <= n; j++)
		{
			int a;
			scanf("%1d", &a);
			if(a == 0) continue;
			M.a[(j - 1) * 9 + 1][(i - 1) * 9 + a] = 1;
		}
	}
	N.a[1][1] = 1;
	Matrix R = power(M, t) * N;
	printf("%d", R.a[(n - 1) * 9 + 1][1]);
	return 0;
}