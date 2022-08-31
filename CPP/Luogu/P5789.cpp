#include <cstdio>
const int mod = 2017;
struct Matrix
{
	int N;
	int a[205][205];
	Matrix()
	{
		for(int i = 0; i <= 200; i++)
		{
			for(int j = 0; j <= 200; j++)
			{
				a[i][j] = 0;
			}
		}
		N = 0;
	}
	void Set(int x)
	{
		N = x;
		for(int i = 1; i <= N; i++)
		{
			for(int j = 1; j <= N; j++)
			{
				a[i][j] = 0;
			}
		}
		for(int i = 1; i <= N; i++)
		{
			a[i][i] = 1;
		}
	}
	Matrix operator*(const Matrix & A) const
	{
		Matrix R;
		R.N = N;
		for(int i = 1; i <= N; i++)
		{
			for(int k = 1; k <= N; k++)
			{
				if(a[i][k] == 0) continue;
				for(int j = 1; j <= N; j++)
				{
					(R.a[i][j] += a[i][k] * A.a[k][j] % mod) %= mod;
				}
			}
		}
		return R;
	}
	void print()
	{
		for(int i = 1; i <= N; i++)
		{
			for(int j = 1; j <= N; j++)
			{
				printf("%d ", a[i][j]);
			}
			printf("\n");
		}
	}
};
Matrix power(Matrix X, int k)
{
	Matrix R;
	R.Set(X.N);
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
void add_edge(int u, int v)
{
	M.a[u][v] = 1;
}
int main()
{
	int n, m;
	scanf("%d%d", &n, &m);
	M.N = 2 * n;
	for(int i = 1; i <= m; i++)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		add_edge(u, v);
		add_edge(v, u);
	}
	for(int i = 1; i <= n; i++)
	{
		add_edge(i, i + n);
		add_edge(i, i);
		add_edge(i + n, i + n);
	}
	//M.print();
	int t;
	scanf("%d", &t);
	Matrix R = power(M, t);
	int ans = 0;
	//R.print();
	for(int i = 1; i <= 2 * n; i++)
	{
		(ans += R.a[1][i]) %= mod;
	}
	printf("%d", ans);
	return 0;
}