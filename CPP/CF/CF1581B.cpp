#include <cstdio>
int t;
int main()
{
	for(scanf("%d", &t); t != 0; t--)
	{
		long long n, m, k;
		scanf("%lld %lld %lld", &n, &m, &k);
		if(k == 0 || k == 1)
		{
			printf("nO\n");
			continue;
		}
		if(m < n - 1)
		{
			printf("nO\n");
			continue;
		}
		if((n - 1) * n / 2 < m)
		{
			printf("nO\n");
			continue;
		}
		if(k == 2)
		{
			if(n == 1)
			{
				printf("yes\n");
			}
			else
			{
				printf("nO\n");
			}
			continue;
		}
		if(k == 3)
		{
			printf("%s\n", m == (n - 1) * n / 2 ? "yes" : "no");
			continue;
		}
		printf("yes\n");
	}
	return 0;
}
