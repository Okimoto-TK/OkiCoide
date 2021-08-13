#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>
#define INF 0x3f3f3f3f
int head[300];
struct edge
{
	int u, v, f, nxt;
	edge() { u = v = f = nxt = -1; }
	edge(int a, int b, int c)
	{
		u = a;
		v = b;
		f = c;
		nxt = head[a];
	}
} e[900000];
int m, n, ptr, s, t;
void add_edge(int a, int b, int c)
{
	e[ptr] = edge(a, b, c);
	head[a] = ptr++;
	e[ptr] = edge(b, a, 0);
	head[b] = ptr++;
}
int dep[300];
bool bfs()
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
int cur[300];
int dfs(int u, int f)
{
	if(u == t) return f;
	int fsum = 0;
	for(int i = cur[u]; i != -1; i = e[i].nxt)
	{
		cur[u] = i;
		int v = e[i].v;
		if(dep[v] == dep[u] + 1 && e[i].f > 0)
		{
			int _f = dfs(v, std::min(f, e[i].f));
			e[i].f -= _f;
			e[i ^ 1].f += _f;
			f -= _f;
			fsum += _f;
		}
	}
	return fsum;
}
std::queue<int> ans1;
std::queue<int> ans2;
bool vis[300];
int run()
{
	int ans = 0;
	while(bfs())
	{
		memcpy(cur, head, sizeof(head));
		ans += dfs(s, INF);
	}
	return ans;
}
char buf[1000];
int main()
{
	int sum = 0;
	memset(head, -1, sizeof(head));
	scanf("%d%d", &m, &n);
	s = m + n + 1;
	t = s + 1;
	for(int i = 1; i <= m; i++)
	{
		int p;
		scanf("%d", &p);
		add_edge(s, i, p);
		sum += p;
		int r;
		for(scanf("%d", &r); r != 0; scanf("%d", &r))
		{
			add_edge(i, r + m, INF);
		}
	}
	for(int i = 1; i <= n; i++)
	{
		int c;
		scanf("%d", &c);
		add_edge(i + m, t, c);
	}
	printf("%d", sum - run());
	return 0;
}

