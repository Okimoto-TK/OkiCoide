#include <cstdio>
#define MAX 130
const int mod = 45989;
struct Matrix
{
	int n, m;
	int ma[MAX+5][MAX+5];
	Matrix()
	{
		for(int i = 1; i <= MAX; i++)
		{
			for(int j = 1; j <= MAX; j++)
			{
				ma[i][j] = 0;
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
				if(ma[i][k] == 0) continue;
				for(int j = 1; j <= A.m; j++)
				{
					(R.ma[i][j] += ma[i][k] * A.ma[k][j] % mod) %= mod;
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
				printf("%d ", ma[i][j]);
			}
			putchar('\n');
		}
		putchar('\n');
	}
};
struct Edge
{
	int u, v;
} e[MAX+5];
Matrix qpow(Matrix X, int k)
{
	Matrix R;
	R.n = X.n;
	R.m = X.m;
	for(int i = 1; i <= R.n; i++)
	{
		R.ma[i][i] = 1;
	}
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
int n, m, t, a, b;
Matrix M, N;
int main()
{
	scanf("%d%d%d%d%d", &n, &m, &t, &a, &b);
	M.n = M.m = N.n = 2 * m;
	N.m = 1;
	for(int i = 1; i <= m; i++)
	{
		scanf("%d%d", &e[i].u, &e[i].v);
		for(int j = 1; j < i; j++)
		{
			if(e[i].u == e[j].u)
			{
				M.ma[j * 2 - 1][i * 2]++;
				M.ma[i * 2 - 1][j * 2]++;
			}
			if(e[i].u == e[j].v)
			{
				M.ma[i * 2 - 1][j * 2 - 1]++;
				M.ma[j * 2][i * 2]++;
			}
			if(e[i].v == e[j].v)
			{
				M.ma[j * 2][i * 2 - 1]++;
				M.ma[i * 2][j * 2 - 1]++;
			}
			if(e[i].v == e[j].u)
			{
				M.ma[j * 2 - 1][i * 2 - 1]++;
				M.ma[i * 2][j * 2]++;
			}
		}
		if(e[i].u == a)
		{
			N.ma[i * 2 - 1][1] = 1;
		}
		if(e[i].v == a)
		{
			N.ma[i * 2][1] = 1;
		}
	}
	//M.print();
	Matrix R = qpow(M, t - 1);
	//R.print();
	R = R * N;
	//N.print();
	int ans = 0;
	for(int i = 1; i <= m; i++)
	{
		if(e[i].v == b)
		{
			(ans += R.ma[i * 2 - 1][1]) %= mod;
		}
		if(e[i].u == b)
		{
			(ans += R.ma[i * 2][1]) %= mod;
		}
	}
	printf("%d", ans);
	return 0;
}