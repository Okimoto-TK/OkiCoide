#include <cstdio>
#include <algorithm>
#define N 5000000
const int mod = 998244353;
long long power(long long x, long long k)
{
	long long r = 1;
	while(k)
	{
		if(k & 1) (r *= x) %= mod;
		(x *= x) %= mod;
		k >>= 1;
	}
	return r;
}
long long k;
int tot;
bool npr[2 * N + 5];
int pr[N + 5];
int f[N + 5];
int inv[N + 5];
int fsum[N + 5];
int idk[2 * N + 5];
int sum[2 * N + 5];
int ksum[N + 5];
void esv()
{
	idk[1] = 1;
	f[1] = 1;
	for(int i = 2; i <= N; i++)
	{
		if(!npr[i])
		{
			pr[++tot] = i;
			f[i] = i - 1;
			inv[i] = power(i - 1, mod - 2);
			idk[i] = power(i, k);
		}
		for(int j = 1; j <= tot && i * pr[j] <= 2 * N; j++)
		{
			idk[i * pr[j]] = 1ll * idk[i] * idk[pr[j]] % mod;
			npr[i * pr[j]] = true;
			if(i * pr[j] > N) continue;
			if(i % pr[j] == 0)
			{
				if((i / pr[j]) % pr[j] != 0)
				{
					f[i * pr[j]] = 1ll * f[i] * (inv[pr[j]]) % mod * (-pr[j]) % mod;
				}
				else
				{
					f[i * pr[j]] = 0;
				}
				break;
			}
			f[i * pr[j]] = 1ll * f[i] * f[pr[j]] % mod;
		}
	}
}
void init()
{
	for(int i = N + 1; i <= 2 * N; i++)
	{
		if(!npr[i])
		{
			pr[++tot] = i;
			idk[i] = power(i, k);
		}
		for(int j = 1; j <= tot && i * pr[j] <= 2 * N; j++)
		{
			idk[i * pr[j]] = 1ll * idk[i] * idk[pr[j]] % mod;
			npr[i * pr[j]] = true;
			if(i % pr[j] == 0)
			{
				break;
			}	
		}
	}
	for(int i = 1; i <= N; i++)
	{
		fsum[i] = (1ll * fsum[i - 1] + 1ll * idk[i] * f[i] % mod) % mod;
	}
	for(int i = 1; i <= 2 * N; i++)
	{
		sum[i] = (1ll * sum[i - 1] + idk[i]) % mod;
	}
	for(int i = 1; i <= N; i++)
	{
		ksum[i] = (1ll * ksum[i - 1] + 2ll * (sum[2 * i - 1] - sum[i]) + 1ll * idk[2 * i]) % mod;
	}
}
int main()
{
	int n;
	scanf("%d%lld", &n, &k);
	esv();
	init();
	int l = 1, r;
	long long ans = 0;
	for(; l <= n; l = r + 1)
	{
		r = n / (n / l);
		(ans += 1ll * (fsum[r] - fsum[l - 1]) * 1ll * ksum[n / l] % mod) %= mod;
	}
	printf("%lld", (ans + mod) % mod);
	return 0;
}