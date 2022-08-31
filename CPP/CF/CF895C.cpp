#include <cstdio>
const int mod = 1e9 + 7;
int pr[20];
bool npr[100];
int tot;
int a[100005];
int n;
struct Bas
{
	int cnt;
	int bas[20];
	void insert(int x)
	{
		for(int d = 19; d >= 0; d--)
		{
			if(x & (1 << d))
			{
				if(bas[d] == 0)
				{
					bas[d] = x;
					cnt++;
					break;
				}
				else
				{
					x ^= bas[d];
				}
			}
		}
	}
} B;
long long qpow(long long x, int k)
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
	for(int i = 2; i <= 70; i++)
	{
		if(!npr[i])
		{
			pr[++tot] = i;
		}
		for(int j = 1; j <= tot && i * pr[j] <= 70; j++)
		{
			npr[i * pr[j]] = true;
			if(i % pr[j] == 0)
			{
				break;
			}
		}
	}
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
	{
		int x;
		scanf("%d", &x);
		for(int j = 1; j <= tot && x != 1; j++)
		{
			int cnt = 0;
			while(x % pr[j] == 0)
			{
				cnt++;
				x /= pr[j];
			}
			if(cnt % 2 == 1)
			{
				a[i] += (1 << (j - 1));
			}
		}
		B.insert(a[i]);
	}
	printf("%lld", qpow(2, n - B.cnt) - 1);
	return 0;
}