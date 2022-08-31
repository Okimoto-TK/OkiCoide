#include <cstdio>
#include <map>
#define N 200
struct Matrix
{
	int ma[205][205];
	int n;
	Matrix()
	{
		for(int i = 1; i <= N; i++)
		{
			for(int j = 1; j <= N; j++)
			{
				ma[i][j] = 0x3f3f3f3f;
			}
		}
	}
	void reset()
	{
		for(int i = 1; i <= N; i++)
		{
			for(int j = 1; j <= N; j++)
			{
				ma[i][j] = 0;
			}
		}
	}
	Matrix operator*(const Matrix & A) const
	{
		Matrix R;
		R.n = n;
		for(int i = 1; i <= n; i++)
		{
			for(int j = 1; j <= n; j++)
			{
				for(int k = 1; k <= n; k++)
				{
					R.ma[i][j] = std::min(R.ma[i][j], ma[i][k] + A.ma[k][j]);
				}
			}
		}
		return R;
	}
	void print()
	{
		for(int i = 1; i <= n; i++)
		{
			for(int j = 1; j <= n; j++)
			{
				if(ma[i][j] == 0x3f3f3f3f)
				{
					printf("X ");
				}
				else
				{
					printf("%d ", ma[i][j]);
				}
			}
			printf("\n");
		}
	}
};
int a[1005];
int b[205];
int tot;
Matrix M;
Matrix power(Matrix X, int k)
{
	Matrix R = X;
	//R.print();
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
	//R.print();
	return R;
}
int main()
{
	int n, t, s, e;
	scanf("%d%d%d%d", &n, &t, &s, &e);
	for(int i = 1; i <= t; i++)
	{
		int u, v, w;
		scanf("%d%d%d", &w, &u, &v);
		if(a[u] == 0)
		{
			a[u] = ++tot;
			b[tot] = u;
		}
		if(a[v] == 0)
		{
			a[v] = ++tot;
			b[tot] = v;
		}
		M.ma[a[u]][a[v]] = w;
		M.ma[a[v]][a[u]] = w;
	}
	M.n = tot;
	Matrix R = power(M, n);
	printf("%d", R.ma[a[s]][a[e]]);
	return 0;
}