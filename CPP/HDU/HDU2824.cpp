#include <cstdio>
#define N 3000000
bool nprime[N + 5];
int phi[N + 5];
int pr[N + 5];
int tot;
int main()
{
	phi[1] = 1;
	for(int i = 2; i <= N; i++)
	{
		if(!nprime[i])
		{
			phi[i] = i - 1;
			pr[++tot] = i;
		}
		for(int j = 1; j <= tot && pr[j] * i <= N; j++)
		{
			nprime[i * pr[j]] = true;
			if(i % pr[j] == 0)
			{
				phi[i * pr[j]] = pr[j] * phi[i];
				break;
			}
			phi[i * pr[j]] = (pr[j] - 1) * phi[i];
		}
	}
	int a, b;
	while(scanf("%d", &a) != EOF)
	{
		scanf("%d", &b);
		long long ans = 0;
		for(int i = a; i <= b; i++)
		{
			ans += phi[i];
		}
		printf("%lld\n", ans);
	}
	return 0;
}