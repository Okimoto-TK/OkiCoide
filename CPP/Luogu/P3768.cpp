#include <cstdio>
#include <cmath>
#include <algorithm>
#include <unordered_map>
#define MAX 10000000
int N;
long long mod;
int tot;
bool npr[MAX + 5];
int pr[MAX + 5];
long long f[MAX + 5];
long long fsum[MAX + 5];
void esv()
{
	f[1] = 1;
	for(int i = 2; i <= N; i++)
	{
		if(!npr[i])
		{
			pr[++tot] = i;
			f[i] = 1ll * i * i % mod * (i - 1) % mod;
		}
		for(int j = 1; j <= tot && i * pr[j] <= N; j++)
		{
			npr[i * pr[j]] = true;
			if(i % pr[j] == 0)
			{
				f[i * pr[j]] = f[i] * pr[j] % mod * pr[j] % mod * pr[j] % mod;
				break;
			}
			f[i * pr[j]] = f[i] * f[pr[j]] % mod;
		}
	}
	for(int i = 1; i <= N; i++)
	{
		fsum[i] = (fsum[i - 1] + f[i]) % mod;
	}
}
long long power(long long x, int k)
{
	long long r = 1;
	while(k)
	{
		if(k&1) (r *= x) %= mod;
		(x *= x) %= mod;
		k >>= 1;
	}
	return r;
}
long long inv2, inv6;
long long sum3(long long n)
{
	long long r = n % mod * ((n + 1) % mod) % mod * inv2 % mod;
	return r * r % mod;
}
long long sum2(long long n)
{
	return n % mod * ((n + 1) % mod) % mod * ((2 * n + 1) % mod) % mod * inv6 % mod;
}
long long sum1(long long n)
{
	return n % mod * ((n + 1) % mod) % mod * inv2 % mod;
}
std::unordered_map<long long, long long> hs;
long long dusv(long long n)
{
	if(n <= N) return fsum[n];
	if(hs.count(n)) return hs[n];
	long long ans = sum3(n);
	long long l = 2, r;
	long long last2 = 1, this2;
	for(; l <= n; l = r + 1)
	{
		r = n / (n / l);
		this2 = sum2(r);
		(ans -= (this2 - last2) % mod * dusv(n / l) % mod) %= mod;
		last2 = this2;
	}
	return hs[n] = ans;
}
int main()
{
	long long n;
	scanf("%lld%lld", &mod, &n);
	if(n <= MAX) N = n;
	else N = MAX;
	//N = 1;
	esv();
	inv2 = power(2, mod - 2);
	inv6 = power(6, mod - 2);
	long long l = 1, r;
	long long lasts = 0, thiss;
	long long ans = 0;
	for(; l <= n; l = r + 1)
	{
		r = n / (n / l);
		thiss = dusv(r);
		(ans += (thiss - lasts) % mod * sum1(n / l) % mod * sum1(n / l) % mod) %= mod;
		lasts = thiss;
	}
	printf("%lld", (ans + mod) % mod);
	return 0;
}