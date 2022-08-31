#include <cstdio>
const int mod = 19260817;
struct Matrix
{
	int n, m;
	long long a[5][5];
	Matrix()
	{
		for(int i = 0; i < 5; i++)
		{
			for(int j = 0; j < 5; j++)
			{
				a[i][j] = 0;
			}
		}
	}
	Matrix(int x)
	{
		for(int i = 0; i < 5; i++)
		{
			for(int j = 0; j < 5; j++)
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
		printf("\n");
	}
};
Matrix qpow(Matrix X, int k)
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
Matrix M;
int main()
{
	M.a[1][1] = M.a[1][2] = M.a[1][3] = M.a[2][1] = M.a[3][2] = 1;
	M.n = M.m = 3;
	//M.print();
	int m;
	scanf("%d", &m);
	for(int i = 1; i <= m; i++)
	{
		int n;
		scanf("%d", &n);
		Matrix R = qpow(M, n);
		//R.print();
		printf("%lld\n", (R.a[1][1] + R.a[2][1] + R.a[3][1]) % mod); 
	}
}