#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#define N 200000
#define SN 450
int n, bs;
int ans[N + 5];
int a[N + 5];
int b[N + 5];
int c[N + 5];
int cnt[N + 5];
int sum[N + 5];
int tmp[N + 5];
int g[SN + 5][N + 5];
std::vector<int> nxt[N + 5];
void solve()
{
	memset(cnt, 0, sizeof(cnt));
	memset(ans, 0, sizeof(ans));
	scanf("%d", &n);
	bs = sqrt(n);
	for(int i = 1; i <= n; i++)
	{
		scanf("%d", &a[i]);
		b[i] = a[i];
	}
	std::sort(b + 1, b + 1 + n);
	int len = std::unique(b + 1, b + 1 + n) - (b + 1);
	for(int i = 1; i <= len; i++)
	{
		nxt[i].clear();
	}
	for(int i = 1; i <= n; i++)
	{
		a[i] = std::lower_bound(b + 1, b + 1 + len, a[i]) - b;
		cnt[a[i]]++;
		nxt[a[i]].push_back(i);
	}
	for(int i = 1; i <= len; i++)
	{
		if(cnt[i] > bs)
		{
			for(int j = 1; j <= n; j++)
			{
				sum[j] = sum[j - 1] + (a[j] == i);
			}
			for(int j = 1; j <= len; j++)
			{
				if(i == j) continue;
				int tmp = 0;
				int max = 0;
				int last = 0;
				for(auto p : nxt[j])
				{
					tmp -= sum[p] - sum[last];
					if(tmp < 0)
					{
						tmp = 0;
					}
					tmp++;
					max = std::max(max, tmp);
					last = p;
				}
				ans[i] = std::max(ans[i], max);
				//printf("-%d %d\n", b[i], ans[i]);
				tmp = 0;
				max = 0;
				last = 0;
				for(auto p : nxt[j])
				{
					tmp += sum[p] - sum[last];
					max = std::max(max, tmp);
					last = p;
					tmp--;
					//printf("%d%d\n", tmp, p);
					if(tmp < 0)
					{
						tmp = 0;
					}
				}
				//max += sum[n] - sum[last];
				ans[j] = std::max(ans[j], max);
				//printf("--%d %d\n", b[j], ans[j]);
			}
		}
		//printf("%d\n", i);
	}
	memset(g, 0x3f, sizeof(g));
	for(int i = 1; i <= bs; i++)
	{
		memset(tmp, 0, sizeof(tmp));
		int mode = 0;
		for(int l = 1, r = 0; l <= n; tmp[a[l++]]--)
		{
			while(r < n && tmp[mode] < i)
			{
				tmp[a[++r]]++;
				if(tmp[a[r]] > tmp[mode]) mode = a[r];
			}
			if(r <= n && tmp[mode] == i)
			{
				g[i][l] = std::min(g[i][l], r);
			}
		}
	}
	/*
	for(int i = 1; i <= n; i++)
	{
		for(int j = 1; j <= bs; j++)
		{
			if(g[j][i] >= 0x3f3f3f3f)
			{
				printf("-1 ");
			}
			else
			{
				printf("%d ", g[j][i]);
			}
		}
		printf("\n");
	}
	*/
	for(int c = 1; c <= len; c++)
	{
		//printf("%d", c);
		if(cnt[c] > bs) continue;
		for(int j = 1; j <= bs; j++)
		{
			int k = 0;
			if(g[j][1] < 0x3f3f3f3f)
			{
				while(k < cnt[c] && nxt[c][k] <= g[j][1])
				{
					k++;
				}
				//printf("^%d %d %d\n", j, c, k);
				ans[c] = std::max(ans[c], j - k);
				//printf("---%d %d\n", b[c], ans[c]);
			}
			for(int i = 0, k = 1; i < cnt[c]; i++)
			{
				if(g[j][nxt[c][i] + 1] >= 0x3f3f3f3f) continue;
				while(k < cnt[c] && nxt[c][k] <= g[j][nxt[c][i] + 1])
				{
					k++;
				}
				//printf("^^%d %d %d\n", j, c, k);
				ans[c] = std::max(ans[c], j - k + i + 1);
				//printf("----%d %d\n", b[c], ans[c]);
			}
		}
	}
	int max = 0;
	for(int i = 1; i <= len; i++)
	{
		ans[i] += nxt[i].size();
		max = std::max(max, ans[i]);
	}
	printf("%d\n", max);
	for(int i = 1; i <= len; i++)
	{
		if(ans[i] == max)
		{
			printf("%d\n", b[i]);
		}
	}
}
int main()
{
	freopen("in.in", "r", stdin);
	int T;
	for(scanf("%d", &T); T; T--)
	{
		solve();
	}
	return 0;
}