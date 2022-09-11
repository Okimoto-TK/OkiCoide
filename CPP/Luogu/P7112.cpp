#include <cstdio>
#include <algorithm>
long long n, p;
long long a[605][605];
long long det()
{
	int w = 1;
	for(int i = 1; i <= n; i++)
	{
		for(int j = i + 1; j <= n; j++)
		{
			while(a[i][i])
			{
				int d = a[j][i] / a[i][i];
				for(int k = i; k <= n; k++)
				{
					a[j][k] = (a[j][k] - a[i][k] * d % p) % p;
				}
				std::swap(a[i], a[j]);
				w *= -1;
			}
			std::swap(a[i], a[j]);
			w *= -1;
		}
	}
	int ans = 1;
	for(int i = 1; i <= n; i++)
	{
		ans = ans * a[i][i] % p;
	}
	return ans * w;
}
int main()
{
	scanf("%lld%lld", &n, &p);
	for(int i = 1; i <= n; i++)
	{
		for(int j = 1; j <= n; j++)
		{
			scanf("%lld", &a[i][j]);
		}
	}
	printf("%lld", (det() % p + p) % p);
	return 0;
}