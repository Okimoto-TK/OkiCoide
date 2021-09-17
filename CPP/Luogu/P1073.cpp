#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#define N 100005
int head[N * 2];
struct edge
{
	int u, v, nxt;
	edge() { u = v = nxt = -1; }
	edge(int a, int b)
	{
		u = a;
		v = b;
		nxt = head[a];
	}
} e[2000005];
int n, m, ptr, pool, cnt, top;
int a[N];
int dfn[N];
int low[N];
int lnk[N];
int min[N];
int max[N];
int stk[N];
int idg[N];
inline void add_edge(int a, int b, int c)
{
	e[ptr] = edge(a, b);
	head[a] = ptr++;
	if(c == 2)
	{
		e[ptr] = edge(b, a);
		head[b] = ptr++;
	}
}
void dfs(int u)
{
	low[u] = dfn[u] = ++pool;
	int end = top;
	stk[top++] = u;
	for(int i = head[u]; i != -1; i = e[i].nxt)
	{
		int v = e[i].v;
		if(dfn[v] == 0)
		{
			dfs(v);
			low[u] = std::min(low[u], low[v]);
		}
		else if(lnk[v] == 0) low[u] = std::min(low[u], dfn[v]);
	}
	if(low[u] == dfn[u])
	{
		int p = ++cnt;
		while(top != end)
		{
			min[p] = std::min(min[p], a[stk[--top]]);
			max[p] = std::max(max[p], a[stk[top]]);
			lnk[stk[top]] = p;
		}
	}
}
inline void link()
{
	for(int i = 1; i <= n; i++)
	{
		int u = lnk[i];
		for(int j = head[i]; j != -1; j = e[j].nxt)
		{
			int v = lnk[e[j].v];
			if(u == v) continue;
			add_edge(u + n, v + n, 1);
			idg[v]++;
		}
	}
}
int f[N];
inline int bfs()
{
	std::queue<int> q;
	q.push(lnk[1]);
	while(!q.empty())
	{
		int u = q.front();
		q.pop();
		for(int i = head[u + n]; i != -1; i = e[i].nxt)
		{
			int v = e[i].v - n;
			min[v] = std::min(min[v], min[u]);
			f[v] = std::max(f[u], max[v] - min[v]);
			if(--idg[v] == 0) q.push(v);
		}
	}
	return f[lnk[n]];
}
int main()
{
	memset(min, 0x3f, sizeof(min));
	memset(head, -1, sizeof(head));
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++)
	{
		scanf("%d", &a[i]);
	}
	for(int i = 1; i <= m; i++)
	{
		int x, y, z;
		scanf("%d%d%d", &x, &y, &z);
		add_edge(x, y, z);
	}
	for(int i = 1; i <= n; i++)
	{
		if(dfn[i] == 0) dfs(i);
	}
	link();
	printf("%d", bfs());
	return 0;
}
