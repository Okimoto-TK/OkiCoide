#include <cstdio>
const int mod = 1000000007;
struct Matrix
{
	int n, m;
	long long a[5][5];
	Matrix()
	{
		n = m = 0;
		for(int i = 1; i <= 3; i++)
		{
			for(int j = 1; j <= 3; j++)
			{
				a[i][j] = 0;
			}
		}
	}
	Matrix(int x)
	{
		n = m = 0;
		for(int i = 1; i <= 3; i++)
		{
			for(int j = 1; j <= 3; j++)
			{
				a[i][j] = 0;
			}
		}
		for(int i = 1; i <= 3; i++)
		{
			a[i][i] = 1;
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
	void print()
	{
		for(int i = 1; i <= n; i++)
		{
			for(int j = 1; j <= m; j++)
			{
				printf("%lld ", a[i][j]);
			}
			printf("\n");
		}
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
Matrix N, M;
Matrix ANS;
int n, m;
int main()
{
	ANS.a[1][1] = 1;
	N.n = N.m = M.m = M.n = ANS.n = 3;
	ANS.m = 1;
	N.a[1][1] = N.a[1][3] = N.a[2][2] = N.a[3][1] = N.a[3][2] = 1;
	N.a[2][1] = N.a[2][3] = N.a[3][3] = 2;
	M.a[1][1] = M.a[2][2] = M.a[3][1] = M.a[3][2] = M.a[3][3] = 1;
	M.a[2][1] = 2;
	scanf("%d%d", &n, &m);
	int last = 0;
	for(int i = 1; i <= m; i++)
	{
		int x;
		scanf("%d", &x);
		ANS = power(N, x - last) * ANS;
		ANS = M * ANS;
		last = x + 1;
	}
	ANS = power(N, n - last) * ANS;
	printf("%lld", ANS.a[3][1] % mod);
	return 0;
}