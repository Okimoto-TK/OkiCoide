#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>
#define N 30000
#define M 200
int n1, n2, tot, pool, p, s, t;
int head[N * 5 + 5];
int pr[M + 5];
bool vis[N * 5 + 5];
int dis[N * 5 + 5];
int cur[N * 5 + 5];
struct Edge
{
	int v, nxt, f;
} e[N * 1000 + 5];
struct Item
{
	int a, b, c;
} l1[N + 5], l2[N + 5];
std::queue<int> q;
std::vector<int> fac[M + 5];
void init()
{
	memset(head, -1, sizeof(head));
	for(int i = 2; i <= M; i++)
	{
		bool isp = true;
		for(int j = 2; j * j <= i; j++)
		{
			if(i % j == 0)
			{
				isp = false;
				break;
			}
		}
		if(isp)
		{
			pr[++tot] = i;
		}
	}
	for(int i = 2; i <= M; i++)
	{
		for(int j = 1; j <= tot; j++)
		{
			if(i % pr[j] == 0)
			{
				fac[i].push_back(j);
			}
		}
	}
}
int get_id(int x, int y)
{
	return (x - 1) * tot + y + n1 + n2;
}
void add_edge(int u, int v, int f)
{
	e[p].v = v;
	e[p].nxt = head[u];
	e[p].f = f;
	head[u] = p++;
	e[p].v = u;
	e[p].nxt = head[v];
	e[p].f = 0;
	head[v] = p++;
}
void res(int u, int x, int y, int d)
{
	for(auto i : fac[x])
	{
		for(auto j : fac[y])
		{
			if(u <= n1) add_edge(u, get_id(i, j) + d * tot * tot, 1);
			else add_edge(get_id(i, j) + d * tot * tot, u, 1);
		}
	}
}
bool bfs()
{
	memset(vis, 0, sizeof(vis));
	vis[s] = true;
	dis[s] = 0;
	q.push(s);
	while(!q.empty())
	{
		int u = q.front();
		q.pop();
		for(int i = head[u]; i != -1; i = e[i].nxt)
		{
			if(!vis[e[i].v] && e[i].f > 0)
			{
				dis[e[i].v] = dis[u] + 1;
				vis[e[i].v] = true;
				q.push(e[i].v);
			}
		}
	}
	return vis[t];
}
int dfs(int u, int flow)
{
	if(u == t || flow == 0) return flow;
	int fsum = 0, f;
	for(int i = cur[u]; i != -1; i = e[i].nxt)
	{
		cur[u] = i;
		if(dis[u] + 1 == dis[e[i].v] && (f = dfs(e[i].v, std::min(flow, e[i].f))) > 0)
		{
			e[i].f -= f;
			e[i^1].f += f;
			fsum += f;
			flow -= f;
			if(flow == 0) break;
		}
	}
	return fsum;
}
int dinic()
{
	int flow = 0;
	while(bfs())
	{
		memcpy(cur, head, sizeof(cur));
		flow += dfs(s, 0x3f3f3f3f);
	}
	return flow;
}
int main()
{
	init();
	scanf("%d%d", &n1, &n2);
	s = n1 + n2 + tot * tot * 3 + 1;
	t = s + 1;
	for(int i = 1; i <= n1; i++)
	{
		scanf("%d%d%d", &l1[i].a, &l1[i].b, &l1[i].c);
		add_edge(s, i, 1);
		res(i, l1[i].a, l1[i].b, 0);
		res(i, l1[i].a, l1[i].c, 1);
		res(i, l1[i].b, l1[i].c, 2);
	}
	for(int i = 1; i <= n2; i++)
	{
		scanf("%d%d%d", &l2[i].a, &l2[i].b, &l2[i].c);
		add_edge(i + n1, t, 1);
		res(i + n1, l2[i].a, l2[i].b, 0);
		res(i + n1, l2[i].a, l2[i].c, 1);
		res(i + n1, l2[i].b, l2[i].c, 2);
	}
	printf("%d", dinic());
	return 0;
}