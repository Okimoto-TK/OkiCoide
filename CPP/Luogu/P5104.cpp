#include <cstdio>
#define P 1000000007
unsigned long long w, n, k;
unsigned long long power(unsigned long long x, unsigned long long k)
{
	unsigned long long r = 1;
	while(k != 0)
	{
		if((k & 1) != 0) (r *= x) %= P;
		(x *= x) %= P;
		k >>= 1;
	}
	return r;
}
int main()
{
	scanf("%llu%llu%llu", &w, &n, &k);
	printf("%llu", (w * power(power(2, k), P - 2) % P));
	return 0;
}
