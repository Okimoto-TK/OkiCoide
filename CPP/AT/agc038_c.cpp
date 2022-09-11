#include <cstdio>
#include <algorithm>
#define N 1000000
const int mod = 998244353;
long long power(long long x, int k)
{
	long long r = 1;
	while(k)
	{
		if(k&1) (r *= x) %= mod;
		(x *= x)  %= mod;
		k >>= 1;
	}
	return r;
}
int tot;
bool npr[N + 5];
int pr[N + 5];
long long inv[N + 5];
long long f[N + 5];
void esv()
{
	f[1] = 1;
	for(int i = 2; i <= N; i++)
	{
		if(!npr[i])
		{
			pr[++tot] = i;
			inv[i] = power(i, mod - 2);
			f[i] = inv[i] - 1;
		}
		for(int j = 1; j <= tot && pr[j] * i <= N; j++)
		{
			npr[i * pr[j]] = true;
			if(i % pr[j] == 0)
			{
				(f[i * pr[j]] = f[i] * inv[pr[j]]) %= mod;
				break;
			}
			(f[i * pr[j]] = f[i] * f[pr[j]]) %= mod;
		}
	}
}
int n;
int a[N + 5];
int cnt[N + 5];
long long sum[N + 5];
void init()
{
	for(int i = 1; i <= n; i++)
	{
		cnt[a[i]]++;
	}
	for(int i = 1; i <= N; i++)
	{
		for(int j = 1; i * j <= N; j++)
		{
			(sum[i] += 1ll * i * j * cnt[i * j]) %= mod;
		}
	}
}
int main()
{
	esv();
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
	{
		scanf("%d", &a[i]);
	}
	init();
	long long ans = 0;
	for(int t = 1; t <= N; t++)
	{
		(ans += f[t] * sum[t] % mod * sum[t] % mod) %= mod;
	}
	for(int i = 1; i <= n; i++)
	{
		(ans -= a[i]) %= mod;
	}
	printf("%lld", (ans * power(2, mod - 2) % mod + mod) % mod);
	return 0;
}