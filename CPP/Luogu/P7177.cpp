#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#define N 1000
int p;
int head[N + 5];
struct Edge
{
	int v, t, nxt;
	double x;
} e[(N << 1) + 5];
void add_edge(int u, int v, int x, int t)
{
	e[p].v = v;
	e[p].nxt = head[u];
	e[p].t = t;
	e[p].x = x;
	head[u] = p++;
}
int n;
double need[N + 5];
double req[N + 5];
void dfs(int u, int fa)
{
	if(need[u] >= 0)
	{
		req[u] = need[u];
		return;
	}
	for(int i = head[u]; i != -1; i = e[i].nxt)
	{
		int v = e[i].v;
		if(v == fa) continue;
		dfs(v, u);
		if(e[i].t)
		{
			req[u] = std::max(sqrt(req[v]) * 100.0 / e[i].x, req[u]);
		}
		else
		{
			req[u] = std::max(req[v] * 100.0 / e[i].x, req[u]);
		}
	}
}
int main()
{
	memset(head, -1, sizeof(head));
	scanf("%d", &n);
	for(int i = 1; i < n; i++)
	{
		int a, b, x, t;
		scanf("%d%d%d%d", &a, &b, &x, &t);
		add_edge(a, b, x, t);
		add_edge(b, a, x, t);
	}
	for(int i = 1; i <= n; i++)
	{
		scanf("%lf", &need[i]);
	}
	dfs(1, 0);
	printf("%.3lf", req[1]);
	return 0;
}