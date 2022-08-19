#include <cstdio>
#define N 1000
int tot;
bool npr[N + 5];
int pr[N + 5];
int mu[N + 5];
int sum[N + 5];
void mobius()
{
	mu[1] = 1;
	for(int i = 2; i <= N; i++)
	{
		if(!npr[i])
		{
			pr[++tot] = i;
			mu[i] = -1;
		}
		for(int j = 1; j <= tot && i * pr[j] <= N; j++)
		{
			npr[i * pr[j]] = true;
			if(i % pr[j] == 0)
			{
				mu[i * pr[j]] = 0;
				break;
			}
			mu[i * pr[j]] = -mu[i];
		}
	}
	for(int i = 1; i <= N; i++)
	{
		sum[i] = sum[i - 1] + mu[i];
	}
}
int t, n;
int main()
{
	mobius();
	scanf("%d", &t);
	for(int i = 1; i <= t; i++)
	{
		scanf("%d", &n);
		int l = 1, r;
		int ans = 0;
		for(; l <= n; l = r + 1)
		{
			r = n / (n / l);
			ans += (sum[r] - sum[l - 1]) * (n / l) * (n / l);
		}
		printf("%d %d %d\n", i, n, ans + 2);
	}
	return 0;
}