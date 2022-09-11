#include <cstdio>
#include <algorithm>
#include <vector>
int n, m;
int pool, max;
int root[300005];
struct node
{
	int del;
	int lc, rc;
} t[20000000];
void remove(int & k, int l, int r, int x)
{
	if(!k)
	{
		k = ++pool;
	}
	t[k].del++;
	if(l == r)
	{
		return;
	}
	int mid = (l + r) >> 1;
	if(x <= mid)
	{
		remove(t[k].lc, l, mid, x);
	}
	else
	{
		remove(t[k].rc, mid + 1, r, x);
	}
	t[k].del = t[t[k].lc].del + t[t[k].rc].del;
}
int find(int k, int l, int r, int v)
{
	// if k == 0: not visited -> no element removed -> del = 0
	if(l == r)
	{
		return l;
	}
	int mid = (l + r) >> 1;
	int lcnt = mid - l + 1 - t[t[k].lc].del;
	if(lcnt >= v)
	{
		return find(t[k].lc, l, mid, v);
	}
	else
	{
		return find(t[k].rc, mid + 1, r, v - lcnt);
	}
}
std::vector<long long> vec[400005];
long long solve1(int rem, long long add)
{
	int pos = find(root[n + 1], 1, max, rem);
	remove(root[n + 1], 1, max, pos);
	long long tar;
	if(pos <= n)
	{
		tar = 1ll * pos * m;
	}
	else
	{
		tar = vec[n + 1][pos - n - 1];
	}
	if(add == 0)
	{
		vec[n + 1].push_back(tar);
	}
	else
	{
		vec[n + 1].push_back(add);
	}
	return tar;
}
long long solve2(int x, int y)
{
	//printf("--1\n");
	int pos = find(root[x], 1, max, y);
	remove(root[x], 1, max, pos);
	//printf("--2\n");
	long long tar;
	//printf("++%d %d\n", pos, vec[x].size());
	if(pos <= m - 1)
	{
		tar = 1ll * (x - 1) * m + pos; 
	}
	else
	{
		tar = vec[x][pos - m];
	}
	//printf("--3\n");
	vec[x].push_back(solve1(x, tar));
	//printf("--4\n");
	return tar;
}
int main()
{
	scanf("%d%d", &n, &m);
	int q;
	scanf("%d", &q);
	max = std::max(n, m) + q + 5;
	for(int i = 1; i <= q; i++)
	{
		int x, y;
		scanf("%d%d", &x, &y);
		if(y == m)
		{
			printf("%lld\n", solve1(x, 0));
		}
		else
		{
			printf("%lld\n", solve2(x, y));
		}
	}
}