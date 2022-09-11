#include <cstdio>
#include <cmath>
#include <algorithm>
#define N 200000
#define SN 5000
const int mod = 998244353;
int bs;
int n, m, max;
int a[N + 5];
int o[N + 5];
int d[N + 5];
int B[N + 5];
int L[SN + 5];
int R[SN + 5];
int S[SN + 5];
int cnt1[SN + 5];
int lazy[SN + 5];
int _lazy[SN + 5];
void change(int i)
{
	if(o[i] > 0)
	{
		o[i]--;
	}
	else
	{
		if(_lazy[B[i]] == d[i] && lazy[B[i]] > 0)
		{
			d[i]++;
			_lazy[B[i]]++;
			lazy[B[i]]--;
			return;
		}
		else if(_lazy[B[i]] > d[i])
		{
			d[i]++;
			return;
		}
		if(a[i] > 1 && a[i] < 4) cnt1[B[i]]++;
		a[i] = (int)sqrt(a[i]);
	}
}
void _sqrt(int l, int r)
{
	int LB = B[l];
	int RB = B[r];
	if(RB - LB <= 1)
	{
		for(int i = l; i <= r; i++)
		{
			change(i);
		}
		return;
	}
	for(int i = LB + 1; i < RB; i++)
	{
		if(cnt1[i] == S[i]) continue;
		if(lazy[i] > 0)
		{
			lazy[i]--;
		}
		else
		{
			for(int j = L[i]; j <= R[i]; j++)
			{
				change(j);
			}
		}
	}
	for(int i = l; i <= R[LB]; i++)
	{
		change(i);
	}
	for(int i = L[RB]; i <= r; i++)
	{
		change(i);
	}
}
void pow2(int l, int r)
{
	int LB = B[l];
	int RB = B[r];
	if(RB - LB <= 1)
	{
		for(int i = l; i <= r; i++)
		{
			o[i]++;
		}
		return;
	}
	for(int i = LB + 1; i < RB; i++)
	{
		if(cnt1[i] == S[i]) continue;
		lazy[i]++;
	}
	for(int i = l; i <= R[LB]; i++)
	{
		o[i]++;
	}
	for(int i = L[RB]; i <= r; i++)
	{
		o[i]++;
	}
}
long long power(long long x, int k, int p)
{
	long long r = 1;
	while(k)
	{
		if(k & 1)
		{
			(r *= x) %= p;
		}
		(x *= x) %= p;
		k >>= 1;
	}
	return r;
}
long long flat()
{
	for(int i = 1; i <= max; i++)
	{
		for(int j = L[i]; j <= R[i]; j++)
		{
			o[j] += _lazy[i] + lazy[i] - d[j];
		}
	}
	long long r = 0;
	for(int i = 1; i <= n; i++)
	{
		r += power(a[i], power(2, o[i], mod - 1), mod);
		r %= mod;
	}
	return r;
}
int main()
{
	scanf("%d%d", &n, &m);
	bs = sqrt(n);
	for(int i = 1; i <= n; i++)
	{
		scanf("%d", &a[i]);
	}
	max = ceil(double(n) / bs);
	for(int i = 1; i <= max; i++)
	{
		L[i] = R[i - 1] + 1;
		R[i] = std::min(n, bs * i);
		S[i] = R[i] - L[i] + 1;
		for(int j = L[i]; j <= R[i]; j++)
		{
			B[j] = i;
			if(a[j] == 1) cnt1[i]++;
		}
	}
	for(int i = 1; i <= m; i++)
	{
		int op, l, r;
		scanf("%d%d%d", &op, &l, &r);
		if(op == 1)
		{
			_sqrt(l, r);
		}
		else
		{
			pow2(l, r);
		}
	}
	printf("%lld", flat());
	return 0;
}