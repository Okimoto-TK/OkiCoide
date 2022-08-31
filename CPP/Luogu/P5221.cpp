#include <cstdio>
#include <bitset>
#define N 1000000
std::bitset<N + 5> npr;
const int mod = 104857601;
int phi[N + 5];
void ersv()
{
	phi[1] = 1;
	for(int i = 2; i <= N; i++)
	{
		if(!npr[i])
		{
			phi[i] = i - 1;
		}
		for(int j = 2; j * i <= N; j++)
		{
			if(npr[i * j]) continue;
			if(npr[j]) continue;
			npr[i * j] = true;
			if(i % j == 0)
			{
				phi[i * j] = phi[i] * j;
				break;
			}
			phi[i * j] = phi[i] * (j - 1);
		}
	}
	for(int i = 1; i <= N; i++)
	{
		//printf("%d\n", phi[i]);
		(phi[i] += phi[i - 1]) %= (mod - 1);
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
int n;
int main()
{
	ersv();
	scanf("%d", &n);
	long long a = 1;
	long long fac = 1;
	int l = 1, r;
	for(; l <= n; l = r + 1)
	{
		r = n / (n / l);
		long long prod = 1;
		for(int i = l; i <= r; i++) (prod *= i) %= mod;
		(a *= power(prod, 2 * phi[n / l] - 1)) %= mod;
		(fac *= prod) %= mod;
	}
	(a *= a) %= mod;
	a = power(a, mod - 2);
	(a *= power(fac, 2 * n)) %= mod;
	printf("%lld", a);
	return 0;
}