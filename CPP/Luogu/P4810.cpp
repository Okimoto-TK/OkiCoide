#include <cstdio>
#include <vector>
#include <algorithm>
int n;
struct query
{
	int op, v, w;
} q[300005];
int head[300005];
int top[300005];
int fa[300005];
std::vector<int> g[300005];
int son[300005];
int siz[300005];
int dtop[300005];
int dep[300005];
void dfs1(int u)
{
	siz[u] = 1;
	int len = g[u].size();
	for(int i = 0; i < len; i++)
	{
		int v = g[u][i];
		dep[v] = dep[u] + 1;
		dfs1(v);
		siz[u] += siz[v];
		if(siz[son[u]] < siz[v])
		{
			son[u] = v;
		}
	}
}
void dfs2(int u)
{
	if(son[u])
	{
		dtop[son[u]] = dtop[u];
		dfs2(son[u]);
	}
	int len = g[u].size();
	for(int i = 0; i < len; i++)
	{
		int v = g[u][i];
		if(v == son[u]) continue;
		dtop[v] = v;
		dfs2(v);
	}
}
int lca(int x, int y)
{
	int fx = dtop[x], fy = dtop[y];
	while(fx != fy)
	{
		if(dep[fx] < dep[fy])
		{
			std::swap(x, y);
			std::swap(fx, fy);
		}
		x = fa[fx];
		fx = dtop[x];
	}
	if(dep[x] > dep[y])
	{
		std::swap(x, y);
	}
	return x;
}
int main()
{
	//freopen("in.in", "r", stdin);
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
	{
		char op[2];
		scanf("%s%d", op, &q[i].v);
		q[i].op = op[0] - 'a' + 1;
		if(q[i].op == 3)
		{
			scanf("%d", &q[i].w);
		}
		if(q[i].op == 1)
		{
			g[head[q[i].v]].push_back(i);
			top[i] = i;
			head[i] = i;
			fa[i] = head[q[i].v];
		}
		else if(q[i].op == 2)
		{
			head[i] = head[fa[head[q[i].v]]];
		}
		else if(q[i].op == 3)
		{
			head[i] = head[q[i].v];
		}
	}
	dfs1(0);
	dtop[0] = 0;
	dfs2(0);
	for(int i = 1; i <= n; i++)
	{
		if(q[i].op == 1) continue;
		else if(q[i].op == 2)
		{
			printf("%d\n", top[head[q[i].v]]);
		}
		else
		{
			printf("%d\n", dep[lca(head[q[i].v], head[q[i].w])]);
		}
	}
	return 0;	
}
