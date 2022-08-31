#include <cstdio>
#include <algorithm>
#define N 100000
// PRE
// euler sieve
int tot;
bool npr[N + 5];
int pr[N + 5];
int mu[N + 5];
int phi[N + 5];
void esv()
{
	mu[1] = 1;
	phi[1] = 1;
	for(int i = 2; i <= N; i++)
	{
		if(!npr[i])
		{
			pr[++tot] = i;
			mu[i] = -1;
			phi[i] = i - 1;
		}
		for(int j = 1; j <= tot && i * pr[j] <= N; j++)
		{
			npr[i * pr[j]] = true;
			if(i % pr[j] == 0)
			{
				mu[i * pr[j]] = 0;
				phi[i * pr[j]] = phi[i] * pr[j];
				break;
			}
			mu[i * pr[j]] = -mu[i];
			phi[i * pr[j]] = phi[i] * (pr[j] - 1);
		}
	}
}
// quick power
long long mod;
long long power(long long x, long long k)
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
// prefix prod and prefix sum
long long inv[N + 5];
long long f[N + 5];
long long g[N + 5];
long long ginv[N + 5];
long long f2[N + 5];
long long g2[N + 5];
long long g2inv[N + 5];
long long itoi[N + 5];
long long fact[N + 5];
long long factinv[N + 5];
long long phis[N + 5];
long long phit[N + 5];
long long phitinv[N + 5];
void pre()
{
	for(int i = 1; i <= N; i++)
	{
		inv[i] = power(i, mod - 2);
	}
	for(int i = 1; i <= N; i++)
	{
		f[i] = 1;
	}
	for(int t = 1; t <= N; t++)
	{
		for(int d = 1; d * t <= N; d++)
		{
			if(mu[d] == 0) continue;
			if(mu[d] == 1)
			{
				(f[d * t] *= t) %= mod;
			}
			else (f[d * t] *= inv[t]) %= mod;
		}
	}
	for(int T = 1; T <= N; T++)
	{
		f2[T] = power(f[T], 1ll * T * T % (mod - 1));
	}
	ginv[0] = g[0] = g2[0] = g2inv[0] = 1;
	for(int i = 1; i <= N; i++)
	{
		g[i] = (g[i - 1] * f[i]) % mod;
		g2[i] = (g2[i - 1] * f2[i]) % mod;
		ginv[i] = power(g[i], mod - 2);
		g2inv[i] = power(g2[i], mod - 2);
	}
	fact[0] = factinv[0] = phit[0] = phitinv[0] = 1;
	for(int i = 1; i <= N; i++)
	{
		itoi[i] = power(i, i);
		fact[i] = fact[i - 1] * i % mod;
		factinv[i] = power(factinv[i], mod - 2);
		phis[i] = (phis[i - 1] + phi[i]) % (mod - 1);
		phit[i] = phit[i - 1] * power(i, phi[i]) % mod;
		phitinv[i] = power(phit[i], mod - 2);
	}
}
// INIT

// SOL
long long solve1(int A, int B, int C)
{
	long long ans = power(fact[A], B) * power(fact[B], A) % mod;
	int max = std::min(A, B);
	int l = 1, r;
	long long div = 1;
	for(; l <= max; l = r + 1)
	{
		r = std::min(A / (A / l), B / (B / l));
		(div *= power(g[r] * ginv[l - 1] % mod, 1ll * (A / l) * (B / l) % (mod - 1))) %= mod;
	}
	(ans *= power(div, mod - 2)) %= mod;
	ans = power(ans, C);
	l = 1;
	div = 1;
	max = std::min(A, C);
	for(; l <= max; l = r + 1)
	{
		r = std::min(A / (A / l), C / (C / l));
		(div *= power(g[r] * ginv[l - 1] % mod, 1ll * (A / l) * (C / l) % (mod - 1))) %= mod;
	}
	(ans *= power(power(div, B), mod - 2)) %= mod;
	return ans;
}
long long sfact(int x)
{
	long long re = 1;
	for(int i = 2; i <= x; i++)
	{
		(re *= itoi[i]) %= mod;
	}
	return re;
}
long long getSum(long long x)
{
	return (x + 1) * x / 2;
}
long long solve2(long long A, long long B, long long C)
{
	long long ans = power(sfact(A), getSum(B) % (mod - 1)) * power(sfact(B), getSum(A) % (mod - 1)) % mod;
	int max = std::min(A, B);
	int l = 1, r;
	long long div = 1;
	for(; l <= max; l = r + 1)
	{
		r = std::min(A / (A / l), B / (B / l));
		(div *= power(g2[r] * g2inv[l - 1] % mod, getSum(A / l) % (mod - 1) * getSum(B / l) % (mod - 1)) % mod) %= mod;
	}
	(ans *= power(div, mod - 2)) %= mod;
	ans = power(ans, getSum(C) % (mod - 1)); 
	l = 1;
	div = 1;
	max = std::min(A, C);
	for(; l <= max; l = r + 1)
	{
		r = std::min(A / (A / l), C / (C / l));
		(div *= power(g2[r] * g2inv[l - 1] % mod, getSum(A / l) % (mod - 1) * getSum(C / l) % (mod - 1)) % mod) %= mod;
	}
	(ans *= power(power(div, getSum(B) % (mod - 1)), mod - 2)) %= mod;
	return ans;
}
long long getDiv(long long A, long long B)
{
	int max = std::min(A, B);
	int l = 1, r;
	long long div = 1;
	for(; l <= max; l = r + 1)
	{
		r = std::min(A / (A / l), B / (B / l));
		(div *= power(g[r] * ginv[l - 1] % mod, 1ll * (A / l) * (B / l) % (mod - 1))) %= mod;
	}
	return div;
}
long long solve3(long long A, long long B, long long C)
{
	long long ans = 1;
	long long div = 1;
	int max = std::min(A, std::min(B, C));
	int l = 1, r;
	for(; l <= max; l = r + 1)
	{
		//printf("%d\n", 1);
		r = std::min(A / (A / l), std::min(B / (B / l), C / (C / l)));
		(ans *= power(power(fact[A / l], B / l) * power(fact[B / l], A / l) % mod, (C / l) * ((phis[r] - phis[l - 1]) % (mod - 1) + (mod - 1)) % (mod - 1))) %= mod;
		//printf("%d\n", 2);
		(div *= power(getDiv(A / l, B / l), (C / l) * ((phis[r] - phis[l - 1]) % (mod - 1) + (mod - 1)) % (mod - 1))) %= mod;
		(div *= power(getDiv(A / l, C / l), (B / l) * ((phis[r] - phis[l - 1]) % (mod - 1) + (mod - 1)) % (mod - 1))) %= mod;
		//printf("%d\n", 3);
	}
	//printf("%d\n", 4);
	(ans *= power(div, mod - 2)) %= mod;
	return ans;
}
int main()
{
	int T;
	scanf("%d%lld", &T, &mod);
	esv();
	pre();
	for(; T; T--)
	{
		int A, B, C;
		scanf("%d%d%d", &A, &B, &C);
		printf("%lld %lld %lld\n", (solve1(A, B, C) + mod) % mod, (solve2(A, B, C) + mod) % mod, (solve3(A, B, C) + mod) % mod);
	}
}