#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#define N 200005
#define int long long
int n, m, k, q;
int r[N];
int c[N];
int b[N];
int f[N][2];
int g[N][2];
int dp[N][2];
std::vector<int> v[N];
bool preCheck(int x, int a)
{
	return b[x] <= c[a];
}
bool postCheck(int x, int a)
{
	return b[x] >= c[a];
}
int abs(int a)
{
	return a > 0 ? a : -a;
}
int getDist(int x, int y, int z)
{
	return abs(x - z) + abs(y - z);
}
bool cmp(int a, int b)
{
	return c[a] < c[b];
}
signed main()
{
	scanf("%lld%lld%lld%lld", &n, &m, &k, &q);
	for(int i = 1; i <= k; i++)
	{
		scanf("%lld%lld", &r[i], &c[i]);
		v[r[i]].push_back(i);
	}
	r[++k] = 1;
	c[k] = 1;
	v[1].push_back(k);
	for(int i = 1; i <= q; i++)
	{
		scanf("%lld", &b[i]);
	}
	b[q + 1] = m + 1;
	std::sort(b + 1, b + 2 + q);
	for(int i = 1; i <= k; i++)
	{
		int l = 0;
		int r = q;
		while(l < r)
		{
			int mid = (l + r + 1) >> 1;
			if(preCheck(mid, i))
			{
				l = mid;
			}
			else
			{
				r = mid - 1;
			}
		}
		f[i][0] = l;
		l = 1;
		r = q + 1;
		while(l < r)
		{
			int mid = (l + r) >> 1;
			if(postCheck(mid, i))
			{
				r = mid;
			}
			else
			{
				l = mid + 1;
			}	
		}
		f[i][1] = l;
	}
	int pre = 0x3f3f3f3f3f3f3f3f;
	for(int i = 1; i <= n; i++)
	{
		if(v[i].size() > 0)
		{
			std::sort(v[i].begin(), v[i].end(), cmp);
			g[i][0] = v[i][0];
			g[i][1] = v[i][v[i].size() - 1];
			pre = std::min(pre, i);
		}
	}
	memset(dp, 0x3f, sizeof(dp));
	dp[pre][0] = c[g[pre][1]] - 1;
	dp[pre][1] = c[g[pre][0]] - 1;
	for(int i = pre + 1; i <= n; i++)
	{
		if(g[i][0] == 0 && g[i][1] == 0) continue;
		for(int x = 0; x <= 1; x++)
		{
			for(int y = 0; y <= 1; y++)
			{
				if(f[g[i][1 - x]][0] != 0)
				{
					dp[i][x] = std::min(dp[i][x], dp[pre][y] + getDist(c[g[i][1 - x]], c[g[pre][y]], b[f[g[i][1 - x]][0]]));
				}
				if(f[g[i][1 - x]][1] != q + 1)
				{
					dp[i][x] = std::min(dp[i][x], dp[pre][y] + getDist(c[g[i][1 - x]], c[g[pre][y]], b[f[g[i][1 - x]][1]]));
				}
			}
		}
		pre = i;
	}
	dp[pre][0] += pre - 1;
	dp[pre][1] += pre - 1;
	for(int i = 1; i <= pre; i++)
	{
		dp[pre][0] += c[g[i][1]] - c[g[i][0]];
		dp[pre][1] += c[g[i][1]] - c[g[i][0]];
	}
	printf("%lld", std::min(dp[pre][0], dp[pre][1]));
	return 0;
}
