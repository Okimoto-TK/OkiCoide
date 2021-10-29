#include <cstdio>
#include <cstring>
#include <algorithm>
int head[200005];
struct Edge
{
	int v, nxt;
	Edge()
	{
		v = nxt = -1;
	}
	Edge(int a, int b)
	{
		v = b;
		nxt = head[a];
	}
};
int n, ptr;
int vl[200005];
long long f[2][200005];
Edge e[200005];
void addEdge(int a, int b)
{
	e[ptr] = Edge(a, b);
	head[a] = ptr++;
}
void dfs(int u)
{
	f[1][u] = -1e16;
	for(int i = head[u]; i != -1; i = e[i].nxt)
	{
		dfs(e[i].v);
		long long _f[2];
		_f[0] = std::max(f[0][u] + f[0][e[i].v], f[1][u] + f[1][e[i].v]);
		_f[1] = std::max(f[0][u] + f[1][e[i].v], f[1][u] + f[0][e[i].v]);
		f[0][u] = std::max(f[0][u], _f[0]);
		f[1][u] = std::max(f[1][u], _f[1]);
	}
	f[1][u] = std::max(f[0][u] + vl[u], f[1][u]);
}
int main()
{
	memset(head, -1, sizeof(head));
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
	{
		int p;
		scanf("%d%d", &p, &vl[i]);
		addEdge(p == -1 ? 0 : p, i);
	}
	dfs(1);
	printf("%lld", std::max(f[1][1], f[0][1]));
	return 0;
}
