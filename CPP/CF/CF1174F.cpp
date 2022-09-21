#include <cstdio>
#include <vector>
#include <algorithm>
#define N 200000
int siz[N + 5];
int son[N + 5];
int dep[N + 5];
int sup[N + 5];
int n, ansdep, s;
std::vector<int> vec[N + 5];
void dfs1(int u, int fa)
{
	sup[u] = fa;
	dep[u] = dep[fa] + 1;
	if(dep[u] == ansdep) s = u;
	siz[u] = 1;
	for(auto v : vec[u])
	{
		if(v == fa) continue;
		dfs1(v, u);
		siz[u] += siz[v];
		if(siz[v] > siz[son[u]])
		{
			son[u] = v;
		}
	}
}
int kanc(int u, int dis)
{
	while(dis--)
	{
		u = sup[u];
	}
	return u;
}
int getSon(int u)
{
	if(dep[u] == ansdep) return u;
	if(son[u] == 0) return -1;
	return getSon(son[u]);
}
int main()
{
	scanf("%d", &n);
	for(int i = 1; i < n; i++)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		vec[u].push_back(v);
		vec[v].push_back(u);
	}
	printf("d 1\n");
	fflush(stdout);
	scanf("%d", &ansdep);
	ansdep++;
	dfs1(1, 0);
	int dist;
	printf("d %d\n", s);
	fflush(stdout);
	scanf("%d", &dist);
	while(dist != 0)
	{
		int c = kanc(s, dist / 2);
		printf("s %d\n", c);
		fflush(stdout);
		scanf("%d", &c);
		s = getSon(c);
		while(s == -1)
		{
			printf("s %d\n", c);
			fflush(stdout);
			scanf("%d", &c);
			s = getSon(c);
		}
		printf("d %d\n", s);
		fflush(stdout);
		scanf("%d", &dist);
	}
	printf("! %d\n", s);
	return 0;
}
