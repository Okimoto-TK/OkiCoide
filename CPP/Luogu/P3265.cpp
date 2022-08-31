#include <cstdio>
#include <algorithm>
double eps = 1e-5;
int n, m;
struct Vector
{
	int dim;
	double vec[505];
	void divide(const Vector & x, int d)
	{
		double k = vec[d] / x.vec[d];
		for(int i = d; i <= m; i++)
		{
			vec[i] -= k * x.vec[i];
		}
		vec[d] = 0;
	}
};
struct Bas
{
	Vector bas[505];
	bool insert(Vector x)
	{
		for(int d = 1; d <= m; d++)
		{
			if(std::abs(x.vec[d]) > eps)
			{
				if(std::abs(bas[d].vec[d]) < eps)
				{
					bas[d] = x;
					return true;
				}
				else
				{
					x.divide(bas[d], d);
				}
			}
		}
		return false;
	}
} b;
struct item
{
	Vector v;
	int c;
} a[505];
bool cmp(item x, item y)
{
	return x.c < y.c;
}
int main()
{
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++)
	{
		for(int j = 1; j <= m; j++)
		{
			scanf("%lf", &a[i].v.vec[j]);
		}
	}
	for(int i = 1; i <= n; i++)
	{
		scanf("%d", &a[i].c);
	}
	std::sort(a + 1, a + 1 + n, cmp);
	int ans = 0;
	int cost = 0;
	for(int i = 1; i <= n; i++)
	{
		if(b.insert(a[i].v))
		{
			ans++;
			cost += a[i].c;
		}
	}
	printf("%d %d", ans, cost);
	return 0;
}