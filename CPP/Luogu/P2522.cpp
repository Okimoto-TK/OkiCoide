#include <cstdio>
#include <algorithm>
#define N 50000
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
int f(int n, int m, int k)
{
	int max = std::min(n, m) / k;
	int l = 1, r;
	int ans = 0;
	for(; l <= max; l = r + 1)
	{
		r = std::min((n / k) / (n / k / l), (m / k) / (m / k / l));
		ans += (sum[r] - sum[l - 1]) * (n / k / l) * (m / k / l);
	}
	return ans;
}
int n;
int main()
{
	mobius();
	for(scanf("%d", &n); n; n--)
	{
		int a, b, c, d, k;
		scanf("%d%d%d%d%d", &a, &b, &c, &d, &k);
		printf("%d\n", f(b, d, k) - f(a - 1, d, k) - f(b, c - 1, k) + f(a - 1, c - 1, k));
	}
	return 0;
}