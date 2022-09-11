#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <bitset>
#include <vector>
#include <map>
#define N 40000
#define SN 45
inline int read()
{
	int s=0,w=1;
	char c=getchar();
	while(c<'0'||c>'9')
	{
		if(c=='-')
			w=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9')
	{
		s=s*10+c-'0';
		c=getchar();
	}
	return s*w;
}
void write(int x)
{
	if(x<0)
	{
		putchar('-');
		x=-x;
	}
	if(x>=10)
		write(x/10);
	putchar(x%10+'0');
	return;
}
int n, pool, bs, idx, q, top;
int dis[N + 5];
int spc[N + 5];
bool vis[N + 5];
std::vector<int> vec[N + 5];
void dfs1(int u)
{
	//printf("%d\n", u);
	vis[u] = true;
	dis[u] = 0;
	for(auto v : vec[u])
	{
		if(vis[v]) continue;
		dfs1(v);
		if(dis[v] + 1 > dis[u]) dis[u] = dis[v] + 1;
	}
	if(dis[u] > bs)
	{
		dis[u] = 0;
		spc[u] = ++idx;
	}
}
int val[N + 5];
int nxt[N + 5];
int dep[N + 5];
int lca[N + 5][16];
int sta[N + 5];
std::map<int, int> col;
std::bitset<N + 5> f[SN + 5][SN + 5];
void dfs2(int u, int fa, int last)
{
	bool chg = f[0][0][val[u]];
	f[0][0][val[u]] = true;
	if(spc[u])
	{
		nxt[u] = last;
		f[spc[u]][spc[u]] = f[0][0];
		f[0][0].reset();
		f[0][0][val[u]] = true;
		for(auto v : vec[u])
		{
			if(v == fa)
			{
				continue;
			}
			dfs2(v, u, u);
		}
		f[0][0] = f[spc[u]][spc[u]];
	}
	else
	{
		for(auto v : vec[u])
		{
			if(v == fa)
			{
				continue;
			}
			dfs2(v, u, last);
		}
	}
	if(!chg)
	{
		f[0][0][val[u]] = 0;
	}
}
void dfs3(int u, int fa)
{
	dep[u] = dep[fa] + 1;
	lca[u][0] = fa;
	for(int d = 1; (1 << d) <= dep[u]; d++)
	{
		lca[u][d] = lca[lca[u][d - 1]][d - 1];
	}
	for(auto v : vec[u])
	{
		if(v == fa) continue;
		dfs3(v, u);
	}
}
void dfs4(int u, int fa)
{
	if(spc[u] != 0)
	{
		for(int i = 1; i <= top; i++)
		{
			f[spc[u]][sta[i]] = f[spc[u]][spc[u]];
			f[spc[u]][sta[i]] |= f[sta[top]][sta[i]];
		}
		sta[++top] = spc[u];
	}
	for(auto v : vec[u])
	{
		if(v == fa) continue;
		dfs4(v, u);
	}
	if(spc[u] != 0)
	{
		top--;
	}
}
int Lca(int x, int y)
{
	if(dep[x] < dep[y])
	{
		std::swap(x, y);
	}
	for(int d = 15; d >= 0; d--)
	{
		if(dep[lca[x][d]] >= dep[y])
		{
			x = lca[x][d];
		}
	}
	if(x == y) return x;
	for(int d = 15; d >= 0; d--)
	{
		if(lca[x][d] != lca[y][d])
		{
			x = lca[x][d];
			y = lca[y][d];
		}
	}
	return lca[x][0];
}
std::bitset<N + 5> ans;
int solve(int x, int y)
{	
	int c = Lca(x, y);
	ans.reset();
	int B = (spc[x] != 0) ? x : 0;
	for(int i = x ? x : 0; spc[i] == 0 && i != c; i = lca[i][0])
	{
		ans[val[i]] = true;
		B = (spc[lca[i][0]] != 0) ? lca[i][0] : 0;
	}
	if(B != 0)
	{
		int S = B;
		int E = 0;
		for(; dep[nxt[B]] >= dep[c]; B = nxt[B])
		{
			E = B;
		}
		if(E != 0)
		{
			ans |= f[spc[S]][spc[E]];
		}
		for(int i = B; i != c; i = lca[i][0])
		{
			ans[val[i]] = true;
		}
	}
	B = (spc[y] != 0) ? y : 0;
	for(int i = y; spc[i] == 0 && i != c; i = lca[i][0])
	{
		ans[val[i]] = true;
		B = (spc[lca[i][0]] != 0) ? lca[i][0] : 0;
	}
	if(B != 0)
	{
		int S = B;
		int E = 0;
		for(; dep[nxt[B]] >= dep[c]; B = nxt[B])
		{
			E = B;
		}
		if(E != 0)
		{
			ans |= f[spc[S]][spc[E]];
		}
		for(int i = B; i != c; i = lca[i][0])
		{
			ans[val[i]] = true;
		}
	}
	ans[val[c]] = true;
	return ans.count();
}
int main()
{
	//freopen("in.in", "r", stdin);
	//freopen("out.out", "w", stdout);
	//freopen("out.out", "w", stdout);
	n = read();
	q = read();
	bs = 1000;
	for(int i = 1; i <= n; i++)
	{
		val[i] = read();
		if(col[val[i]] == 0)
		{
			col[val[i]] = ++pool;
		}
		val[i] = col[val[i]];
	}
	for(int i = 1; i < n; i++)
	{
		int u = read(), v = read();
		vec[u].push_back(v);
		vec[v].push_back(u);
	}
	dfs1(1);
	dfs2(1, 0, 0);
	dfs3(1, 0);
	dfs4(1, 0);
	int lastans = 0;
	for(int i = 1; i <= q; i++)
	{
		int x = read(), y = read();
		x ^= lastans;
		lastans = solve(x, y);
		write(lastans);
		putchar('\n');
	}
	return 0;
}