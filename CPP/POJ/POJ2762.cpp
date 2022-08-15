#include <cstdio>
#include <cstring>
#include <algorithm>
int n, m, p, pool, buf;
int head[1005];
struct Edge
{
	int u, v, nxt;
} e[10005];
void add_edge(int u, int v)
{
	e[p].u = u;
	e[p].v = v;
	e[p].nxt = head[u];
	head[u] = p++;
}
int dfn[1005];
int low[1005];
int bel[1005];
int stk[1005];
int top;
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
			top--;
			bel[stk[top]] = buf;
		}
	}
}
int deg[1005];
int _deg[1005];
bool conn[1005][1005];
void shrink()
{
	for(int u = 1; u <= n; u++)
	{
		for(int i = head[u]; i != -1; i = e[i].nxt)
		{
			int v = e[i].v;
			if(bel[u] == bel[v]) continue;
			if(!conn[bel[u]][bel[v]])
			{
				conn[bel[u]][bel[v]] = true;
				deg[bel[v]]++;
				_deg[bel[u]]++;
			}
		}
	}
}
void init()
{
	n = m = p = pool = buf = top = 0;
	memset(head, -1, sizeof(head));
	memset(e, 0, sizeof(e));
	memset(low, 0, sizeof(low));
	memset(dfn, 0, sizeof(dfn));
	memset(bel, 0, sizeof(bel));
	memset(stk, 0, sizeof(stk));
	memset(deg, 0, sizeof(deg));
	memset(_deg, 0, sizeof(_deg));
	memset(conn, 0, sizeof(conn));
}
int main()
{
	int T;
	for(scanf("%d", &T); T; T--)
	{
		init();
		scanf("%d%d", &n, &m);
		for(int i = 1; i <= m; i++)
		{
			int u, v;
			scanf("%d%d", &u, &v);
			add_edge(u, v);
		}
		for(int i = 1; i <= n; i++)
		{
			if(!dfn[i])
			{
				tarjan(i);
			}
		}
		shrink();
		int cnt1 = 0, cnt2 = 0;
		bool fail = false;
		for(int i = 1; i <= buf; i++)
		{
			if(deg[i] > 1 || _deg[i] > 1) fail = true;
			if(deg[i] == 0) cnt1++;
			if(_deg[i] == 0) cnt2++;
		}
		if(fail || cnt1 != 1 || cnt2 != 1)
		{
			printf("No\n");
		}
		else
		{
			printf("Yes\n");
		}
	}
	return 0;
}