#include <cstdio>
#include <cstring>
#include <algorithm>
int n, p, pool, buf;
int head[10005];
struct Edge
{
	int u, v, nxt;
} e[5000005];
void add_edge(int u, int v)
{
	e[p].u = u;
	e[p].v = v;
	e[p].nxt = head[u];
	head[u] = p++;
}
int dfn[10005];
int low[10005];
int bel[10005];
int stk[10005];
int top;
int cnt;
int ans;
void tarjan(int u)
{
	dfn[u] = low[u] = ++pool;
	stk[top++] = u;
	for(int i = head[u]; i != -1; i = e[i].nxt)
	{
		int v = e[i].v;
		if(!dfn[v])
		{
			tarjan(v);
			low[u] = std::min(low[u], low[v]);
		}
		else if(!bel[v])
		{
			low[u] = std::min(low[u], dfn[v]);
		}
	}
	if(dfn[u] == low[u])
	{
		++buf;
		while(stk[top] != u)
		{
			--top;
			bel[stk[top]] = buf;
		}
	}
}
int deg[10005];
int _deg[10005];
void shrink()
{
	for(int u = 1; u <= n; u++)
	{
		for(int i = head[u]; i != -1; i = e[i].nxt)
		{
			int v = e[i].v;
			if(bel[u] != bel[v])
			{
				++deg[bel[v]];
				++_deg[bel[u]];
			}
		}
	}
	for(int i = 1; i <= buf; i++)
	{
		if(_deg[i] == 0)
		{
			cnt++;
		}
		if(deg[i] == 0)
		{
			ans++;
		}
	}
}
int main()
{
	memset(head, -1, sizeof(head));
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
	{
		int v;
		for(scanf("%d", &v); v != 0; scanf("%d", &v)) 
		{
			add_edge(i, v);
		}
	}
	for(int i = 1; i <= n; i++)
	{
		if(!dfn[i]) tarjan(i);
	}
	/*
	for(int i = 1; i <= n; i++)
	{
		printf("%d %d\n", i, bel[i]);
	}
	*/
	shrink();
	if(buf == 1)
	{
		printf("%d\n%d", 1, 0);
		return 0;
	}
	printf("%d\n%d", ans, std::max(ans, cnt));
	return 0;
}