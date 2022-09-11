#include <cstdio>
#include <cmath>
#include <vector>
#include <algorithm>
#include <map>
#define N 50000
#define SN 250
int n, m, bs, pool;
int c[N + 5];
int col[SN + 5];
bool in[N + 5];
int L[SN + 5];
int R[SN + 5];
int B[N + 5];
int cnt[SN + 5][N + 5];
std::vector<std::pair<int, int> > rec[N + 5];
std::map<int, int> cn;
int count(int l, int r)
{
	int LB = B[l];
	int RB = B[r];
	if(RB - LB <= 1)
	{
		cn.clear();
		for(int i = l; i <= r; i++)
		{
			cn[c[i]]++;
			if(cn[c[i]] > (r - l + 1) / 2)
			{
				return c[i];
			}
		}
		return 0;
	}
	for(int i = 1; i <= pool; i++)
	{
		int cnt = (*std::upper_bound(rec[col[i]].begin(), rec[col[i]].end(), std::make_pair(r, 0))).second - (*std::lower_bound(rec[col[i]].begin(), rec[col[i]].end(), std::make_pair(l, 0))).second;
		if(cnt > (r - l + 1) / 2) return col[i];
	}
	for(int i = l; i <= R[LB]; i++)
	{
		int cnt = (*std::upper_bound(rec[c[i]].begin(), rec[c[i]].end(), std::make_pair(r, 0))).second - (*std::lower_bound(rec[c[i]].begin(), rec[c[i]].end(), std::make_pair(l, 0))).second;
		if(cnt > (r - l + 1) / 2) return c[i];
	}
	for(int i = L[RB]; i <= r; i++)
	{
		int cnt = (*std::upper_bound(rec[c[i]].begin(), rec[c[i]].end(), std::make_pair(r, 0))).second - (*std::lower_bound(rec[c[i]].begin(), rec[c[i]].end(), std::make_pair(l, 0))).second;
		if(cnt > (r - l + 1) / 2) return c[i];
	}
	return 0;
}
int main()
{
	scanf("%d%d", &n, &m);
	bs = ceil(sqrt(n));
	for(int i = 1; i <= bs; i++)
	{
		L[i] = R[i - 1] + 1;
		R[i] = std::min(n, i * bs);
		for(int j = L[i]; j <= R[i]; j++)
		{
			scanf("%d", &c[j]);
			B[j] = i;
			if(!in[c[j]] && ++cnt[i][c[j]] > (R[i] - L[i] + 1) / 2)
			{
				col[++pool] = c[j];
				in[c[j]] = true;
			}
		}
	}
	for(int i = 1; i <= n; i++)
	{
		rec[c[i]].push_back(std::make_pair(i, rec[c[i]].size()));
	}
	for(int i = 1; i <= m; i++)
	{
		int s, t;
		scanf("%d%d", &s, &t);
		printf("%d\n", count(s, t));
	}
	return 0;
}