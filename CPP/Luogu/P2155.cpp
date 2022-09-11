#include <cstdio>
#define N 10000000
int T, mod;
long long power(long long x, int k)
{
	long long r = 1;
	while(k)
	{
		if(k&1)
		{
			(r *= x) %= mod;
		}
		(x *= x) %= mod;
		k >>= 1;
	}
	return r;
};
bool npr[N + 5];
int pr[N + 5];
int tot;
long long fac[N + 5];
long long div[N + 5];
int main()
{
	scanf("%d %d", &T, &mod);
	fac[0] = 1;
	for(int i = 1; i <= N; i++)
	{
		if(i % mod == 0)
		{
			fac[i] = fac[i - 1];
		}
		else fac[i] = fac[i - 1] * i % mod;
	}
	div[1] = 1;
	for(int i = 2; i <= N; i++)
	{
		div[i] = div[i - 1];
		if(!npr[i])
		{
			pr[++tot] = i;
			if(i % mod != 0) (div[i] *= power(i, mod - 2) * (i - 1) % mod) %= mod;
			else (div[i] *= (i - 1) % mod) %= mod;
		}
		for(int j = 1; j <= tot && i * pr[j] <= N; j++)
		{
			npr[i * pr[j]] = true;
			if(i % pr[j] == 0)
			{
				break;
			}
		}
	}
	for(int i = 1; i <= T; i++)
	{
		int n, m;
		scanf("%d%d", &n, &m);
		if(n / mod > m / mod)
		{
			printf("0\n");
			continue;
		}
		printf("%lld\n", fac[n] * power(fac[m], mod - 2) % mod * fac[m] % mod * div[m] % mod);
	}
	return 0;
}