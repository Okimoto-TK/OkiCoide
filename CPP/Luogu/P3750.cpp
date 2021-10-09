#include <cstdio>
#include <vector>
#define P 100003
int n, m, k;
int a[100005];
long long f[100005];
std::vector<int> fac[100005];
long long power(long long x, int k)
{
	long long r = 1;
	while(k > 0)
	{
		if(k & 1) (r *= x) %= P;
		(x *= x) %= P;
		k >>= 1;
	}
	return r;
}
int main()
{
	scanf("%d%d", &n, &k);
	for(int i = 1; i <= n; i++)
		for(int j = i; j <= n / i; j++)
		{
			fac[i * j].push_back(i);
			if(i != j) fac[i * j].push_back(j);
		}
	int ptr = n;
	for(int i = 1; i <= n; i++)
	{
		scanf("%d", &a[i]);
	}
	while(ptr > 0)
	{
		while(ptr > 0 && a[ptr] == 0) ptr--;
		if(ptr <= 0) break;
		m++;
		for(auto x : fac[ptr]) a[x] ^= 1;
	}
	long long op = 1;
	for(int i = 1; i <= n; i++) (op *= i) %= P;
	if(k >= m)
	{
		printf("%lld", m * op % P);
		return 0;
	}
	f[n] = 0;
	for(int i = n - 1; i >= 0; i--)
	{
		f[i] = power(i + 1, P - 2) * n % P + power(i + 1, P - 2) * (n - i - 1) * f[i + 1] % P;
		f[i] %= P;
	}
	long long ans = 0;
	for(int i = m - 1; i >= k; i--) (ans += f[i]) %= P;
	ans += k;
	printf("%lld", op * ans % P);
	return 0;
}
