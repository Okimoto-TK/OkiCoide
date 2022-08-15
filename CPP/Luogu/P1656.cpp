#include <cstdio>
#include <cstring>
#include <algorithm>
int n, m, pool;
int head[20005];
struct edge
{
	int u, v, nxt;
} e[20005];
void add_edge(int a, int b)
{
	e[pool].u = a;
	e[pool].v = b;
	e[pool].nxt = head[a];
	head[a] = pool++;
}
int cnt;
int dfn[200];
int low[200];
int sup[200];
bool cut[20005];
struct Ans
{
	int a, b;
} ans[20005];
int len;
void tarjan(int u)
{
	low[u] = dfn[u] = ++cnt;
	for(int i = head[u]; i != -1; i = e[i].nxt)
	{
		int v = e[i].v;
		if(i == (sup[u] ^ 1)) continue;
		if(!dfn[v])
		{
			sup[v] = i;
			tarjan(v);
			if(low[v] < low[u]) low[u] = low[v];
			if(low[v] > dfn[u]) cut[i] = cut[i ^ 1] = true;
		}
		else if(dfn[v] < low[u]) low[u] = dfn[v];
	}
}
bool cmp(Ans x, Ans y)
{
	if(x.a == y.a) return x.b < y.b;
	return x.a < y.a;
}
int main()
{
	memset(head, -1, sizeof(head));
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= m; i++)
	{
		int a, b;
		scanf("%d%d", &a, &b);
		if(a > b) std::swap(a, b);
		add_edge(a, b);
		add_edge(b, a);
	}
	tarjan(1);
	for(int i = 0; i < pool; i += 2)
	{
		if(cut[i])
		{
			ans[++len].a = e[i].u;
			ans[len].b = e[i].v;
		}
	}
	std::sort(ans + 1, ans + 1 + len, cmp);
	for(int i = 1; i <= len; i++)
	{
		printf("%d %d\n", ans[i].a, ans[i].b);
	}
	return 0;
}