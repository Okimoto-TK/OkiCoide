#include <cstdio>
#include <cstring>
#include <algorithm>
int n, m, p, pool;
int head[20005];
struct Edge
{
	int u, v, nxt;
} e[80005];
void add_edge(int u, int v)
{
	e[p].u = u;
	e[p].v = v;
	e[p].nxt = head[u];
	head[u] = p++;
}
int dfn[20005];
int low[20005];
int cnt[20005];
bool cut[20005];
struct Ans
{
	int id, val;
} a[20005];
void tarjan(int u)
{
	dfn[u] = low[u] = ++pool;
	for(int i = head[u]; i != -1; i = e[i].nxt)
	{
		int v = e[i].v;
		if(!dfn[v])
		{
			tarjan(v);
			low[u] = std::min(low[u], low[v]);
			if(dfn[u] <= low[v])
			{
				++cnt[u];
				if(u != 1 || cnt[u] > 1) ++a[u].val;
			}
		}
		else low[u] = std::min(low[u], dfn[v]);
	} 
}
bool cmp(Ans x, Ans y)
{
	if(y.val == x.val) return x.id < y.id;
	return x.val > y.val;
}
int main()
{
	//freopen("in.in", "r", stdin);
	//freopen("out.out", "w", stdout);
	for(scanf("%d%d", &n, &m); n != 0 && m != 0; scanf("%d%d", &n, &m))
	{
		memset(head, -1, sizeof(head));
		memset(e, 0, sizeof(e));
		memset(dfn, 0, sizeof(dfn));
		memset(low, 0, sizeof(low));
		memset(cut, 0, sizeof(cut));
		memset(cnt, 0, sizeof(cnt));
		memset(a, 0, sizeof(a));
		for(int i = 1; i <= n; i++)
		{
			a[i].id = i;
		}
		p = pool = 0;
		int u, v;
		for(scanf("%d%d", &u, &v); u != -1 && v != -1; scanf("%d%d", &u, &v))
		{
			u++, v++;
			add_edge(u, v);
			add_edge(v, u);
		}
		tarjan(1);
		std::sort(a + 1, a + 1 + n, cmp);
		for(int i = 1; i <= m; i++)
		{
			printf("%d %d\n", a[i].id - 1, a[i].val + 1);
		}
		printf("\n");
	}
	return 0;
}