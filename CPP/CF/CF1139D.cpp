#include <cstdio>
#include <vector>
#define N 100000
const int mod = 1000000007;
int tot;
bool npr[N + 5];
int pr[N + 5];
int mu[N + 5];
void esv()
{
	mu[1] = 1;
	for(int i = 2; i <= N; i++)
	{
		if(!npr[i])
		{
			mu[i] = -1;
			pr[++tot] = i;
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
int m;
long long inv[N + 5];
long long e[N + 5];
std::vector<int> fac[N + 5];
int main()
{
	esv();
	scanf("%d", &m);
	for(int i = m; i >= 1; i--)
	{
		inv[i] = power(i, mod - 2);
	}
	int sqr = 1;
	for(int i = 1; i <= m; i++)
	{
		if((sqr + 1) * (sqr + 1) <= i) sqr++;
		for(int j = 1; j <= sqr; j++)
		{
			if(i % j == 0)
			{
				fac[i].push_back(j);
				if(i != j * j)
				{
					fac[i].push_back(i / j);
				}
			}
		}
	}
	e[1] = 0;
	for(int i = 2; i <= m; i++)
	{
		long long tmp = m;
		for(auto d : fac[i])
		{
			if(d == i) continue;
			for(auto t : fac[i / d])
			{
				(tmp += e[d] * mu[t] % mod * (m / (d * t)) % mod) %= mod;
			}
		}
		e[i] = tmp * inv[m - (m / i)] % mod;
	}
	long long ans = 0;
	for(int i = 1; i <= m; i++) (ans += e[i]) %= mod;
	(ans *= inv[m]) %= mod;
	ans += 1;
	printf("%lld", (ans % mod + mod) % mod);
	return 0;
}