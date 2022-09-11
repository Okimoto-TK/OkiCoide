#include <cstdio>
#define N 10000000
bool npr[N + 5];
int pr[N + 5];
int phi[N + 5];
long long sum[N + 5];
int tot;
void esv()
{
	phi[1] = sum[1] = 1;
	for(int i = 2; i <= N; i++)
	{
		if(!npr[i])
		{
			pr[++tot] = i;
			phi[i] = i - 1;
		}
		for(int j = 1; j <= tot && i * pr[j] <= N; j++)
		{
			npr[i * pr[j]] = true;
			if(i % pr[j] == 0)
			{
				phi[i * pr[j]] = pr[j] * phi[i];
				break;
			}
			phi[i * pr[j]] = phi[i] * (pr[j] - 1);
		}
		sum[i] = sum[i - 1] + phi[i];
	}
}
int main()
{
	esv();
	int n;
	scanf("%d", &n);
	long long ans = 0;
	for(int i = 1; i <= tot && pr[i] <= n; i++)
	{
		ans += 2 * sum[n / pr[i]] - 1;
	}
	printf("%lld", ans);
	return 0;
}