#include <cstdio>
#include <algorithm>
#define N 50000
bool npr[N + 5];
int pr[N + 5];
int tot;
int mu[N + 5];
int sum[N + 5];
void mobius()
{
	mu[1] = 1;
	for(int i = 2; i <= N; i++)
	{
		if(!npr[i])
		{
			mu[i] = -1;
			pr[++tot] = i;
		}
		for(int j = 1; j <= tot && pr[j] * i <= N; j++)
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
int n;
int a, b, d;
int main()
{
	mobius();
	for(scanf("%d", &n); n; n--)
	{
		scanf("%d %d %d", &a, &b, &d);
		long long ans = 0;
		int l = 1, r;
		for(; l <= std::min(a, b); l = r + 1)
		{
			r = std::min(a / (a / l), b / (b / l));
			ans += (a / (d * l)) * (b / (d * l)) * (sum[r] - sum[l - 1]);
		}
		printf("%lld\n", ans);
	}
	return 0;
}