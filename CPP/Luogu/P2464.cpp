#include <cstdio>
#include <cmath>
#include <algorithm>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/hash_policy.hpp>
#define N 100000
#define SN 1000
int n, m, bs;
int a[N + 5];
int L[SN + 5];
int R[SN + 5];
int B[N + 5];
__gnu_pbds::gp_hash_table<int, int> cnt[SN + 5];
int count(int l, int r, int k)
{
	int LB = B[l];
	int RB = B[r];
	int re = 0;
	if(RB - LB <= 1)
	{
		for(int i = l; i <= r; i++)
		{
			re += (a[i] == k);
		}
		return re;
	}
	for(int i = LB + 1; i < RB; i++)
	{
		re += cnt[i][k];
	}
	for(int i = l; i <= R[LB]; i++)
	{
		re += (a[i] == k);
	}
	for(int i = L[RB]; i <= r; i++)
	{
		re += (a[i] == k);
	}
	return re;
}
void change(int x, int k)
{
	cnt[B[x]][a[x]]--;
	a[x] = k;
	cnt[B[x]][a[x]]++;
}
int main()
{
	scanf("%d%d", &n, &m);
	bs = ceil(sqrt(n));
	for(int i = 1; i <= bs; i++)
	{
		L[i] = R[i - 1] + 1;
		R[i] = std::min(bs * i, n);
		for(int j = L[i]; j <= R[i]; j++)
		{
			scanf("%d", &a[j]);
			cnt[i][a[j]]++;
			B[j] = i;
		}
	}
	for(int i = 1; i <= m; i++)
	{
		char opt[3];
		scanf("%s", opt);
		if(opt[0] == 'Q')
		{
			int a, b, k;
			scanf("%d%d%d", &a, &b, &k);
			printf("%d\n", count(a, b, k));
		}
		else
		{
			int a, p;
			scanf("%d%d", &a, &p);
			change(a, p);
		}
	}
	return 0;
}