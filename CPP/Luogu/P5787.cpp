#include <cstdio>
#include <algorithm>
#include <vector>
#define N 100000
int n, m, k;
struct Edge
{
	int u, v;
} e[N * 2 + 5];
std::vector<int> t[N * 4 + 5];
void change(int k, int l, int r, int x, int y, int v)
{
	if(x <= l && r <= y)
	{
		t[k].push_back(v);
		return;
	}
	int mid = (l + r) >> 1;
	if(x <= mid) change(k << 1, l, mid, x, y, v);
	if(y > mid) change(k << 1 | 1, mid + 1, r, x, y, v);
}
int s[N * 2 + 5];
int size[N * 2 + 5];
void init()
{
	for(int i = 1; i <= 2 * n; i++)
	{
		s[i] = i;
		size[i] = 1;
	}
}
int find(int x)
{
	if(s[x] == x)
	{
		return x;
	}
	return find(s[x]);
}
std::vector<std::pair<int, int> > rec;
void merge(int x, int y)
{
	int fx = find(x);
	int fy = find(y);
	if(fx == fy)
	{
		rec.push_back(std::make_pair(-1, -1));
		return;
	}
	if(size[fx] > size[fy])
	{
		std::swap(fx, fy);
	}
	s[fx] = fy;
	size[fy] += size[fx];
	rec.push_back(std::make_pair(fx, fy));
}
void undo()
{
	auto last = rec.back();
	rec.pop_back();
	if(last.first == -1)
	{
		return;
	}
	s[last.first] = last.first;
	size[last.second] -= size[last.first];
}
void dfs(int k, int l, int r, bool bi)
{
	for(auto i : t[k])
	{
		merge(e[i].u, e[i].v + n);
		merge(e[i].v, e[i].u + n);
		if(find(e[i].u) == find(e[i].u + n) || find(e[i].v) == find(e[i].v + n))
		{
			bi &= false;
		}
	}
	if(l == r)
	{
		printf("%s\n", bi ? "Yes" : "No");
		for(auto i : t[k])
		{
			undo();
			undo();
		}
		return;
	}
	int mid = (l + r) >> 1;
	dfs(k << 1, l, mid, bi);
	dfs(k << 1 | 1, mid + 1, r, bi);
	for(auto i : t[k])
	{
		undo();
		undo();
	}
}
int main()
{
	scanf("%d%d%d", &n, &m, &k);
	init();
	for(int i = 1; i <= m; i++)
	{
		int l, r;
		scanf("%d%d%d%d", &e[i].u, &e[i].v, &l, &r);
		if(l != r) change(1, 1, k, l + 1, r, i);
	}
	dfs(1, 1, n, true);
	return 0;
}