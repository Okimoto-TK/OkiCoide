#include <cstdio>
#define N 100000
bool npr[N + 5];
int pr[N + 5];
int tot;
int mod;
void esv()
{
	for(int i = 2; i <= N; i++)
	{
		if(!npr[i])
		{
			pr[++tot] = i;
		}
		for(int j = 1; j <= tot && i * pr[j] <= N; j++)
		{
			npr[i * pr[j]] = true;
			if(i % pr[j] == 0) break;
		}
	}
}
long long power(long long x, int k)
{
	long long r = 1;
	while(k)
	{
		if(k&1)
		{
			(r *= x) %= mod; 
		}
		(x *= x) %= mod;
		k >>= 1;
	}
	return r;
}
int main()
{
	esv();
	int n;
	scanf("%d", &n);
	mod = n;
	if(npr[n])
	{
		if(n == 4)
		{
			printf("YES\n");
			printf("1\n3\n2\n4\n");
			return 0;
		}
		printf("NO");
		return 0;
	}
	else
	{
		printf("YES\n");
		printf("1\n");
		for(int i = 2; i < n; i++)
		{
			printf("%lld\n", power(i - 1, mod - 2) * i % mod);
		}
		if(n != 1) printf("%d\n", n);
	}
	return 0;
}
