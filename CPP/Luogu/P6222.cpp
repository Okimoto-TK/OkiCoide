#include <cstdio>
#include <bitset>
#include <algorithm>
#define N 10000000
#define P 800000
int _N;
inline unsigned int power(unsigned int x, unsigned int k)
{
	unsigned int r = 1;
	while(k)
	{
		if(k & 1) r *= x;
		x *= x;
		k >>= 1;
	}
	return r;
}
unsigned int k;
int tot;
std::bitset<2 * N + 5> npr;
int pr[2 * P + 5];
// esv1
unsigned int idk[2 * N + 5];
unsigned int sum[2 * N + 5];
unsigned int _idk[N + 5];
void esv1()
{
	_idk[1] = idk[1] = 1;
	for(int i = 2; i <= 2 * _N; i++)
	{
		if(!npr[i])
		{
			pr[++tot] = i;
			idk[i] = power(i, k);
			//if(i <= _N) _idk[i] = idk[i];
		}
		for(int j = 1; j <= tot && i * pr[j] <= 2 * _N; j++)
		{
			idk[i * pr[j]] = idk[i] * idk[pr[j]];
			//if(i * pr[j] <= _N) _idk[i * pr[j]] = idk[i * pr[j]];
			npr[i * pr[j]] = true;
			if(i % pr[j] == 0) break;
		}
	}
	for(int i = 1; i <= _N; i++) _idk[i] = idk[i];
	for(int i = 1; i <= 2 * _N; i++)
	{
		//printf(":%u\n", idk[i]);
		sum[i] = sum[i - 1] + idk[i];
		//printf(":%u\n", sum[i]);
	}
	for(int i = 1; i <= _N; i++)
	{
		idk[i] = idk[i - 1] + 2 * (sum[2 * i - 1] - sum[i]) + idk[2 * i];
		//printf(":%u\n", idk[i]);
	}
}
void esv2()
{
	sum[1] = 1;
	for(int i = 2; i <= _N; i++)
	{
		if(!npr[i])
		{
			sum[i] = i - 1;
		}
		for(int j = 1; j <= tot && pr[j] <= i && i * pr[j] <= _N; j++)
		{
			if(i % pr[j] == 0)
			{
				if((i / pr[j]) % pr[j] != 0)
				{
					sum[i * pr[j]] = sum[i / pr[j]] * (0-pr[j]);
				}
				else
				{
					sum[i * pr[j]] = 0;
				}
				break;
			}
			sum[i * pr[j]] = sum[i] * sum[pr[j]];
		}
	}
	for(int i = 1; i <= _N; i++)
	{
		sum[i] = sum[i - 1] + _idk[i] * sum[i];
	}
}
int main()
{
	int n, t;
	scanf("%d%d%u", &t, &_N, &k);
	esv1();
	esv2();
	for(; t; t--)
	{
		scanf("%d", &n);
		int l = 1, r;
		unsigned int ans = 0;
		for(; l <= n; l = r + 1)
		{
			r = n / (n / l);
			ans += (sum[r] - sum[l - 1]) * idk[n / l];
		}
		printf("%u\n", ans);
	}
	return 0;
}