#include <cstdio>
#include <cstring>
#include <cmath>
#include <queue>
#include <algorithm>
struct Pos
{
	int x, y;
} idv[105], dog[105];
int head[20005];
struct Edge
{
	int u, v, f, nxt;
	Edge() { u = v = f = nxt = -1; }
	Edge(int a, int b, int c)
	{
		u = a;
		v = b;
		f = c;
		nxt = head[a];
	}
} e[8000005];
int n, m, s, t, ptr, pool;
const int inf = 0x3f3f3f3f;
double dis[105];
double GetDis(Pos x, Pos y)
{
	return sqrt(pow(x.x - y.x, 2) + pow(x.y - y.y, 2));
}
void AddEdge(int a, int b, int c)
{
	e[ptr] = Edge(a, b, c);
	head[a] = ptr++;
	e[ptr] = Edge(b, a, 0);
	head[b] = ptr++;
}
int dep[20005];
bool Bfs()
{
	memset(dep, 0, sizeof(dep));
	dep[s] = 1;
	std::queue<int> q;
	q.push(s);
	while(!q.empty())
	{
		int u = q.front();
		q.pop();
		for(int i = head[u]; i != -1; i = e[i].nxt)
		{
			int v = e[i].v;
			if(dep[v] == 0 && e[i].f > 0)
			{
				dep[v] = dep[u] + 1;
				q.push(v);
				if(v == t) break;
			}
		}
	}
	return dep[t] != 0;
}
int cur[20005];
int Dfs(int u, int f)
{
	if(u == t) return f;
	int fsum = 0;
	for(int i = cur[u]; i != -1; i = e[i].nxt)
	{
		cur[u] = i;
		int v = e[i].v;
		if(dep[v] == dep[u] + 1 && e[i].f > 0)
		{
			int _f = Dfs(v, std::min(f, e[i].f));
			e[i].f -= _f;
			e[i ^ 1].f += _f;
			f -= _f;
			fsum += _f;
			if(f <= 0) break;
		}
	}
	return fsum;
}
int Run()
{
	int ans = 0;
	while(Bfs())
	{
		memcpy(cur, head, sizeof(cur));
		ans += Dfs(s, inf);
	}
	return ans;
}
int main()
{
	memset(head, -1, sizeof(head));
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++)
	{
		scanf("%d%d", &idv[i].x, &idv[i].y);
		if(i != 1) dis[i] = dis[i - 1] + GetDis(idv[i], idv[i - 1]);
	}
	for(int i = 1; i <= m; i++)
	{
		scanf("%d%d", &dog[i].x, &dog[i].y);
	}
	s = pool = n + m + 1;
	t = ++pool;
	for(int i = 1; i < n; i++)
	{
		for(int j = 1; j <= m; j++)
		{
			if(GetDis(idv[i], dog[j]) + GetDis(dog[j], idv[i + 1]) <= 2 * dis[i + 1] - 2 * dis[i]) AddEdge(i, j + n, 1);
		}
	}
	for(int i = 1; i <= m; i++) { AddEdge(i + n, t, 1); }
	for(int i = 1; i < n; i++) { AddEdge(s, i, 1); }
	printf("%d\n", Run() + n);
	for(int i = 1; i <= n; i++)
	{
		printf("%d %d ", idv[i].x, idv[i].y);
		for(int j = head[i]; j != -1; j = e[j].nxt)
		{
			if(e[j].f == 0 && e[j].v != s)
			{
				printf("%d %d ", dog[e[j].v - n].x, dog[e[j].v - n].y);
				break;
			}
		}
	}
	return 0;
}
