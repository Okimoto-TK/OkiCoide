#include <cstdio>
#include <algorithm>
int n, k, m;
struct edge
{
	int a, b;
	int T, t;
} e[20005];
bool cmp(edge a, edge b)
{
	return a.T < b.T;
}
int s[10005];
void init()
{
	for(int i = 1; i <= n; i++) s[i] = i;
}
int find(int x)
{
	if(x == s[x]) return x;
	return s[x] = find(s[x]);
}
bool check(int x)
{
	init();
	int _k = 0;
	int c = 0;
	for(int i = 1; i <= m; i++)
	{
		if(find(e[i].a) == find(e[i].b)) continue;
		if(e[i].T <= x)
		{
			s[find(e[i].a)] = find(e[i].b);
			_k++;
			c++;
		}
		else if(e[i].t <= x)
		{
			s[find(e[i].a)] = find(e[i].b);
			c++;
		}
	}
	return c == n - 1 && _k >= k;
}
int main()
{
	scanf("%d%d%d", &n, &k, &m);
	for(int i = 1; i <= m; i++)
	{
		scanf("%d%d%d%d", &e[i].a, &e[i].b, &e[i].T, &e[i].t);
	}
	std::sort(e + 1, e + 1 + m, cmp);
	int l = 0;
	int r = 1e6;
	while(l < r)
	{
		int mid = (l + r) >> 1;
		if(check(mid))
		{
			r = mid;
		}
		else
		{
			l = mid + 1;
		}
	}
	printf("%d", l);
	return 0;
}
