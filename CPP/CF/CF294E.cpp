#include <cstdio>
#include <cstring>
#include <vector>
#define int long long
#define N 5000
int n;
struct wEdge
{
	int v, w, id;
	wEdge()
	{
		v = w = id = 0;
	}
	wEdge(int a, int b, int i)
	{
		v = a, w = b, id = i;
	}
};
std::vector<wEdge> vec[N + 5];
struct Edge
{
	int u, v, w;
} e[N + 5];
int del;
long long f[N + 5];
int siz[N + 5];
int cen;
long long min;
int dfs1(int u, int fa)
{
	siz[u] = 1;
	for(auto & i : vec[u])
	{
		if((u == e[del].u && i.v == e[del].v) || (i.v == e[del].u && u == e[del].v)) continue;
		if(i.v == fa) continue;
		f[u] += dfs1(i.v, u) + siz[i.v] * i.w;
		siz[u] += siz[i.v];
	}
	return f[u];
}
void dfs2(int all, int u, int fa)
{
	if(f[u] < min)
	{
		min = f[u];
		cen = u;
	}
	for(auto & i : vec[u])
	{
		if((u == e[del].u && i.v == e[del].v) || (i.v == e[del].u && u == e[del].v)) continue;
		if(i.v == fa) continue;
		f[i.v] = f[u] + i.w * (all - siz[i.v]) - i.w * (siz[i.v]);
		dfs2(all, i.v, u);
	}
}
long long ans, size[2];
void dfs3(int all, int u, int fa, int col)
{
	//printf("%d %d\n", u, col);
	siz[u] = 1;
	for(auto & i : vec[u])
	{
		if((u == e[del].u && i.v == e[del].v) || (i.v == e[del].u && u == e[del].v)) continue;
		if(i.v == fa) continue;
		dfs3(all, i.v, u, col);
		siz[u] += siz[i.v];
		ans += 1ll * siz[i.v] * (all - siz[i.v] + size[col ^ 1]) * i.w;
	}
}
long long solve(int s1, int s2)
{
	memset(f, 0, sizeof(f));
	//printf("%d %d ", s1, s2);
	ans = 0;
	cen = 0;
	min = 0x3f3f3f3f3f3f3f3f;
	dfs1(s1, 0);
	size[0] = siz[s1];
	dfs2(siz[s1], s1, 0);
	int c1 = cen;
	cen = 0;
	min = 0x3f3f3f3f3f3f3f3f;
	dfs1(s2, 0);
	size[1] = siz[s2];
	dfs2(siz[s2], s2, 1);
	dfs3(siz[s1], c1, 0, 0);
	dfs3(siz[s2], cen, 0, 1);
	ans += 1ll * size[0] * size[1] * e[del].w;
	//printf("%d %d %lld\n", s1, s2, ans);
	return ans;
}
signed main()
{
	//freopen("in.in", "r", stdin);
	scanf("%lld", &n);
	for(int i = 1; i < n; i++)
	{
		int u, v, w;
		scanf("%lld%lld%lld", &u, &v, &w);
		e[i].u = u;
		e[i].v = v;
		e[i].w = w;
		vec[u].push_back(wEdge(v, w, i));
		vec[v].push_back(wEdge(u, w, i));
	}
	long long out = 0x3f3f3f3f3f3f3f3f;
	for(int i = 1; i < n; i++)
	{
		del = i;
		out = std::min(out, solve(e[i].u, e[i].v));
	}
	printf("%lld", out);
	return 0;
}
