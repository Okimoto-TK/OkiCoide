#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>
#define INF 0x3f3f3f3f
#define int long long
int head[40];
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
} e[5000];
int n, m, ptr;
void add_edge(int a, int b, int c)
{
	e[ptr] = edge(a, b, c);
	head[a] = ptr++;
	e[ptr] = edge(b, a, 0);
	head[b] = ptr++;
}
int dep[40];
bool bfs()
{
	memset(dep, 0, sizeof(dep));
	dep[1] = 1;
	std::queue<int> q;
	q.push(1);
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
				if(v == n) break;
			}
		}
	}
	return dep[n] != 0;
}
int cur[40];
int dfs(int u, int f)
{
	if(u == n) return f;
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
			if(f <= 0) break;
		}
	}
	return fsum;
}
void run()
{
	int ans = 0;
	while(bfs())
	{
		memcpy(cur, head, sizeof(head));
		ans += dfs(1, INF);
	}
	printf("%lld %lld", ans / 1005, ans % 1005);
}
signed main()
{
	memset(head, -1, sizeof(head));
	scanf("%lld%lld", &n, &m);
	for(int i = 1; i <= m; i++)
	{
		int a, b, c;
		scanf("%lld%lld%lld", &a, &b, &c);
		add_edge(a, b, c * 1005 + 1);
	}
	run();
	return 0;
}
