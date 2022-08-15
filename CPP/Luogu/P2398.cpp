#include <cstdio>
#define N 100000
int n;
bool npr[N + 5];
int pr[N + 5];
int tot;
int phi[N + 5];
void euler()
{
	phi[1] = 1;
	for(int i = 2; i <= N; i++)
	{
		if(!npr[i])
		{
			pr[++tot] = i;
			phi[i] = i - 1;
		}
		for(int j = 1; j <= tot && pr[j] * i <= N; j++)
		{
			npr[i * pr[j]] = true;
			if(i % pr[j] == 0)
			{
				phi[i * pr[j]] = pr[j] * phi[i];
				break;
			}
			phi[i * pr[j]] = (pr[j] - 1) * phi[i];
		}
	}
}
int main()
{
	euler();
	scanf("%d", &n);
	long long ans = 0;
	for(int T = 1; T <= n; T++)
	{
		ans += 1ll * phi[T] * (n / T) * (n / T);
	}
	printf("%lld", ans);
	return 0;
}