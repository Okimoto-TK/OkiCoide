#include <cstdio>
#include <cmath>
#include <cstring>
#include <vector>
#define N 200000
int n, r, q, lm, p;
int h[N + 5];
std::vector<int> vec[N + 5];
int cnt[N + 5];
int id[N + 5];
struct query
{
	int id, x;
	query()
	{
		id = x = 0;
	}
	query(int a, int b)
	{
		id = a;
		x = b;
	}
};
std::vector<query> q1[N + 5];
std::vector<query> q2[N + 5];
int num[N + 5];
long long ans[N + 5];
void dfs1(int u, int fa)
{
	num[h[u]]++;
	for(auto qu : q1[h[u]])
	{
		ans[qu.id] += num[qu.x];
	}
	for(auto v : vec[u])
	{
		if(v == fa) continue;
		dfs1(v, u);
	}
	num[h[u]]--;
}
void dfs2(int u, int fa)
{
	for(auto qu : q2[h[u]])
	{
		ans[qu.id] -= num[qu.x];
	}
	for(auto v : vec[u])
	{
		if(v == fa) continue;
		dfs2(v, u);
	}
	for(auto qu : q2[h[u]])
	{
		ans[qu.id] += num[qu.x];
	}
	num[h[u]]++;
}
int main()
{
	scanf("%d%d%d", &n, &r, &q);
	lm = sqrt(n);
	scanf("%d", &h[1]);
	cnt[h[1]]++;
	for(int i = 2; i <= n; i++)
	{
		int u;
		scanf("%d%d", &u, &h[i]);
		vec[u].push_back(i);
		cnt[h[i]]++;
	}
	for(int i = 1; i <= q; i++)
	{
		int x, y;
		scanf("%d%d", &x, &y);
		if(cnt[y] <= lm)
		{
			q1[y].push_back(query(i, x));
		}
		else
		{
			q2[x].push_back(query(i, y));
		}
	}
	memset(cnt, 0, sizeof(cnt));
	dfs1(1, 0);
	memset(cnt, 0, sizeof(cnt));
	dfs2(1, 0);
	for(int i = 1; i <= q; i++)
	{
		printf("%lld\n", ans[i]);
	}
	return 0;
}