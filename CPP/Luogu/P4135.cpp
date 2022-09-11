#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/hash_policy.hpp>
#define N 100000
#define SN 400
int n, c, m, bs;
int a[N + 5];
int L[SN + 5];
int R[SN + 5];
int B[N + 5];
int cnt[N + 5];
int ans[SN + 5][SN + 5];
int sum[N + 5][SN + 5];
__gnu_pbds::gp_hash_table<int, int> map;
int query(int l, int r, int id)
{
	map.clear();
	int LB = B[l];
	int RB = B[r];
	if(RB - LB <= 1)
	{
		int re = 0;
		for(int i = l; i <= r; i++)
		{
			if(sum[a[i]][RB] - sum[a[i]][LB - 1] == 1) continue;
			if(map[a[i]] > 0 && map[a[i]] % 2 == 1)
			{
				re++;
			}
			else if(map[a[i]] > 0 && map[a[i]] % 2 == 0)
			{
				re--;
			}
			map[a[i]]++;
		}
		return re;
	}
	int re = ans[LB + 1][RB - 1];
	for(int i = l; i <= R[LB]; i++)
	{
		if(sum[a[i]][RB] - sum[a[i]][LB - 1] == 1) continue;
		if(map[a[i]] == 0)
		{
			map[a[i]] += sum[a[i]][RB - 1] - sum[a[i]][LB];
		}
		if(map[a[i]] > 0 && (map[a[i]] & 1))
		{
			re++;
		}
		else if(map[a[i]] > 0 && !(map[a[i]] & 1))
		{
			re--;
		}
		map[a[i]]++;
	}
	for(int i = L[RB]; i <= r; i++)
	{
		if(sum[a[i]][RB] - sum[a[i]][LB - 1] == 1) continue;
		if(map[a[i]] == 0)
		{
			map[a[i]] += sum[a[i]][RB - 1] - sum[a[i]][LB];
		}
		if(map[a[i]] > 0 && map[a[i]] % 2 == 1)
		{
			re++;
		}
		else if(map[a[i]] > 0 && map[a[i]] % 2 == 0)
		{
			re--;
		}
		map[a[i]]++;
	}
	return re;
}
int main()
{
	//freopen("in.in", "r", stdin);
	//freopen("out.out", "w", stdout);
	scanf("%d%d%d", &n, &c, &m);
	bs = ceil(sqrt(n));
	for(int i = 1; i <= bs; i++)
	{
		L[i] = R[i - 1] + 1;
		R[i] = std::min(n, i * bs);
		for(int j = L[i]; j <= R[i]; j++)
		{
			scanf("%d", &a[j]);
			B[j] = i;
		}
	}
	for(int i = 1; i <= bs; i++)
	{
		memset(cnt, 0, sizeof(cnt));
		for(int j = i; j <= bs; j++)
		{
			if(j != i) ans[i][j] = ans[i][j - 1];
			for(int k = L[j]; k <= R[j]; k++)
			{
				if(cnt[a[k]] > 0 && cnt[a[k]] % 2 == 1)
				{
					ans[i][j]++;
				}
				else if(cnt[a[k]] > 0 && cnt[a[k]] % 2 == 0)
				{
					ans[i][j]--;
				}
				cnt[a[k]]++;
				if(i == 1)
				{
					sum[a[k]][j]++;
				}
			}
		}
	}
	for(int col = 1; col <= c; col++)
	{
		for(int i = 1; i <= bs; i++)
		{
			sum[col][i] = sum[col][i - 1] + sum[col][i];
		}
	}
	int last = 0;
	for(int i = 1; i <= m; i++)
	{
		int l, r;
		scanf("%d%d", &l, &r);
		l = (l + last) % n + 1;
		r = (r + last) % n + 1;
		if(l > r) std::swap(l, r);
		printf("%d\n", last = query(l, r, i));
	}
	return 0;
}