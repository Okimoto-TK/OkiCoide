#include <cstdio>
#include <algorithm>
#define int long long
#define N 4000000
const int mod = 1000000007;
bool npr[N + 5];
int tot;
int pr[N + 5];
int mu[N + 5];
long long h[N + 5];
void esv()
{
	mu[1] = 1;
	h[1] = 1;
	for(int i = 2; i <= N; i++)
	{
		if(!npr[i])
		{
			pr[++tot] = i;
			mu[i] = -1;
			h[i] = (1ll * i * i % mod * i % mod - 1ll * i * i % mod) % mod;
		}
		for(int j = 1; j <= tot && i * pr[j] <= N; j++)
		{
			npr[i * pr[j]] = true;
			if(i % pr[j] == 0)
			{
				mu[i * pr[j]] = 0;
				h[i * pr[j]] = (h[i] * pr[j] % mod * pr[j] % mod * pr[j] % mod) % mod;
				break;
			}
			mu[i * pr[j]] = -mu[i];
			h[i * pr[j]] = (h[i] * h[pr[j]]) % mod;
		}
	}
}
long long getSum(long long x)
{
	return (x + 1) * x / 2 % mod;
}
long long pow2(long long x)
{
	return x * x % mod;
}
long long f[N + 5];
long long BIT[N + 5];
int lowbit(int x)
{
	return x & (-x);
}
void change(int x, long long v)
{
	for(int i = x; i <= N; i += lowbit(i))
	{
		(BIT[i] += v) %= mod;
	}
}
long long query(int x)
{
	long long re = 0;
	for(int i = x; i > 0; i -= lowbit(i))
	{
		(re += BIT[i]) %= mod;
	}
	return re;
}
void init()
{
	for(int i = 1; i <= N; i++)
	{
		//if(i % 100000 == 0) printf("%d\n", i);
		f[i] = (f[i - 1] + h[i]) % mod;
	}
	for(int i = 1; i <= N; i++)
	{
		change(i, 1ll * i * i % mod);
	}
}
int gcd(int a, int b)
{
	if(b == 0) return a;
	return gcd(b, a % b);
}
long long power(long long x, int k)
{
	long long re = 1;
	while(k)
	{
		if(k&1)
		{
			(re *= x) %= mod;
		}
		(x *= x) %= mod;
		k >>=1;
	}
	return re;
}
long long solve(int n)
{
	long long ans = 0;
	int l = 1, r;
	for(; l <= n; l = r + 1)
	{
		r = n / (n / l);
		//printf("%lld\n", l);
		(ans += ((query(r) - query(l - 1)) % mod) * f[n / l] % mod) %= mod;
	}
	return ans;
}
int m, n;
signed main()
{
	//freopen("in.in", "r", stdin);
	esv();
	init();
	scanf("%lld%lld", &m, &n);
	for(int i = 1; i <= m; i++)
	{
		long long x;
		int a, b, k;
		scanf("%lld%lld%lld%lld", &a, &b, &x, &k);
		int d = gcd(a, b);
		long long val = query(d) - query(d - 1);
		//printf("%d %lld\n", d, x % mod * pow2(d) % mod * power(1ll * a * b, mod - 2) % mod);
		change(d, x % mod * pow2(d) % mod * power(1ll * a * b % mod, mod - 2) % mod - val % mod);
		printf("%lld\n", (solve(k) + mod) % mod);
	}
}