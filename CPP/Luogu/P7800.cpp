#include <cstdio>
#include <algorithm>
const int mod = 1000000000;
int N, tot;
int gcd(int a, int b)
{
	if(b == 0) return a;
	return gcd(b, a % b);
}
struct item
{
	int a, b;
} it[320];
bool cmp(item x, item y)
{
	return x.b < y.b;
}
int f[330][230];
int main()
{
	//freopen("tab.out", "w", stdout);
	scanf("%d", &N);
	tot = 0;
	for(int i = 1; i <= N; i++)
	{
		for(int j = i + 1; j <= N; j++)
		{
			if(gcd(i, j) == 1)
			{
				it[++tot].a = i;
				it[tot].b = j;
			}
		}
	}
	std::sort(it + 1, it + 1 + tot, cmp);
	f[1][it[1].b] = 1;
	f[1][1] = 1;
	for(int i = 1; i < tot; i++)
	{
		for(int j = 1; j <= it[i].b; j++)
		{
			(f[i + 1][j] += f[i][j]) %= mod;
			if(it[i + 1].a <= j)
			{
				(f[i + 1][it[i + 1].b] += f[i][j]) %= mod;
			}
			else
			{
				(f[i + 1][j] += f[i][j]) %= mod;
			}
		}
	}
	printf("%d", f[tot][N]);
}