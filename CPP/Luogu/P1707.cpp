#include <cstdio>
#include <cstring>
long long mod;
long long safeMul(long long x, long long y)
{
	long long pow10[20];
	x %= mod;
	y %= mod;
	pow10[0] = x;
	for(int i = 1; i <= 17; i++)
	{
		pow10[i] = pow10[i - 1] * 10 % mod;
	}
	long long ans = 0;
	for(int i = 0; y != 0; i++, y /= 10)
	{
		ans = (ans + pow10[i] * (y % 10)) % mod;
	}
	return ans;
}
struct Matrix
{
	int n, m;
	long long a[15][15];
	Matrix()
	{
		memset(a, 0, sizeof(a));
	}
	Matrix(int x)
	{
		memset(a, 0, sizeof(a));
		for(int i = 0; i < 15; i++)
		{
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
					(R.a[i][j] += safeMul(a[i][k], A.a[k][j])) %= mod; 
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
Matrix qpow(Matrix X, long long k)
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
long long n;
Matrix M;
Matrix N;
int main()
{
	M.n = M.m = N.n = 11;
	N.m = 1;
	scanf("%lld%lld", &n, &mod);
	scanf("%d%d%d%d", &M.a[1][1], &M.a[1][2], &M.a[1][7], &M.a[1][8]);
	scanf("%d%d%d", &M.a[3][3], &M.a[3][4], &M.a[9][9]);
	N.a[9][1] = M.a[9][9];
	scanf("%d%d%d", &M.a[5][5], &M.a[5][6], &M.a[10][10]);
	N.a[10][1] = M.a[10][10];
	M.a[1][3] = M.a[1][5] = M.a[1][11] = 1;
	M.a[2][1] = 1;
	M.a[3][1] = M.a[3][5] = M.a[3][9] = 1;
	M.a[4][3] = 1;
	M.a[5][1] = M.a[5][3] = M.a[5][8] = M.a[5][10] = 1;
	M.a[5][11] = 2;
	M.a[6][5] = 1;
	M.a[7][7] = 1;
	M.a[7][8] = 2;
	M.a[7][11] = 1;
	M.a[8][8] = 1;
	M.a[8][11] = 1;
	M.a[11][11] = 1;
	N.a[2][1] = N.a[4][1] = N.a[6][1] = N.a[7][1] = N.a[8][1] = N.a[11][1] = 1;
	N.a[1][1] = N.a[3][1] = N.a[5][1] = 3;
	if(n <= 2)
	{
		printf("1 1 1\n");
	}
	else
	{
		//M.print();
		Matrix R = qpow(M, n - 2);
		//R.print();
		R = R * N;
		printf("nodgd %lld\nCiocio %lld\nNicole %lld", R.a[1][1], R.a[3][1], R.a[5][1]);
	}
 	return 0;
}