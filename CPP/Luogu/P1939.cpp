#include <cstdio>
const int mod = 1e9 + 7;
int base[3][3] = {{1, 0, 1}, {1, 0, 0}, {0, 1, 0}};
struct Matrix
{
	long long ma[3][3];
	Matrix()
	{
		for(int i = 0; i <= 2; i++)
		{
			for(int j = 0; j <= 2; j++)
			{
				ma[i][j] = 0;
			}
		}
	}
	Matrix(int x)
	{
		for(int i = 0; i <= 2; i++)
		{
			for(int j = 0; j <= 2; j++)
			{
				ma[i][j] = 0;
			}
		}
		ma[0][0] = ma[1][1] = ma[2][2] = x;
	}
	Matrix(bool kind, int x[3][3])
	{
		for(int i = 0; i <= 2; i++)
		{
			for(int j = 0; j <= 2; j++)
			{
				ma[i][j] = x[i][j];
			}
		}
	}
	Matrix operator*(const Matrix & A) const 
	{
		Matrix R;
		for(int i = 0; i < 3; i++)
		{
			for(int j = 0; j < 3; j++)
			{
				for(int k = 0; k < 3; k++)
				{
					(R.ma[i][j] += ma[i][k] * A.ma[k][j] % mod) %= mod;
				}
			}
		}
		return R;
	}
	void print()
	{
		for(int i = 0; i < 3; i++)
		{
			for(int j = 0; j < 3; j++)
			{
				printf("%lld ", ma[i][j]);
			}
			printf("\n");
		}
	}
};
const Matrix Base = Matrix(false, base);
Matrix power(Matrix x, int k)
{
	Matrix r = Matrix(1);
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
int main()
{
	int T;
	for(scanf("%d", &T); T; T--)
	{
		int n;
		scanf("%d", &n);
		if(n <= 3)
		{
			printf("%d\n", 1);
			continue;
		}
		Matrix r = power(Base, n - 3);
		printf("%lld\n", (r.ma[0][0] + r.ma[0][1] + r.ma[0][2]) % mod);
	}
}