#include <cstdio>
#include <cmath>
#define N 1000000
int mod;
bool npr[2 * N + 5];
int pr[200005];
int nu[2 * N + 5];
int tot;
void esv()
{
	for(int i = 2; i <= 2 * N; i++)
	{
		if(!npr[i])
		{
			pr[++tot] = i;
			nu[i] = tot;
		}
		for(int j = 1; j <= tot && i * pr[j] <= 2 * N; j++)
		{
			npr[i * pr[j]] = true;
			if(i % pr[j] == 0) break;
		}
	}
}
int prc[200005];
void res(int x, int op)
{
	int max = sqrt(x);
	for(int i = 1; i <= tot && pr[i] <= max && x != 1; i++)
	{
		while(x % pr[i] == 0)
		{
			prc[i] += op;
			x /= pr[i];
		}
	}
	if(x != 1)
	{
		prc[nu[x]] += op;
	}
}
int n, p;
long long power(long long x, int k)
{
	long long r = 1;
	while(k)
	{
		if(k&1)
		{
			(r *= x) %= p;
		}
		(x *= x) %= p;
		k >>= 1;
	}
	return r;
}
int main()
{
	esv();
	scanf("%d%d", &n, &p);
	for(int i = n + 1; i <= 2 * n; i++)
	{
		res(i, 1);
	}
	for(int i = 1; i <= n; i++)
	{
		res(i, -1);
	}
	res(n + 1, -1);
	long long ans = 1;
	for(int i = 1; i <= tot; i++)
	{
		(ans *= power(pr[i], prc[i])) %= p;
	}
	printf("%lld", ans);
	return 0;
}