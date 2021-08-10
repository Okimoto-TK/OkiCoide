#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>
#define INF 0x7f7f7f7f
int head[3005];
int cur[3005];
struct edge
{
	int u;
	int v;
	int f;
	int nxt;
	edge() { u = v = f = nxt = -1; }
	edge(int a, int b, int c)
	{
		u = a;
		v = b;
		f = c;
		nxt = head[a];
	}
} e[2000005];
int ptr;
int n, m;
int cnt, sum;
int s, t;
void add_edge(int a, int b, int c)
{
	e[ptr] = edge(a, b, c);
	head[a] = ptr++;
	e[ptr] = edge(b, a, 0);
	head[b] = ptr++;
}
int dep[3005];
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
				if(v == t) return true;
			}
		}
	}
	return dep[t] != 0;
}
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
			if(f <= 0) break;
		}
	}
	return fsum;
}
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
int main()
{
	memset(head, -1, sizeof(head));
	scanf("%d", &n);
	cnt = n;
	s = ++cnt;
	t = ++cnt;
	for(int i = 1; i <= n; i++)
	{
		int a;
		scanf("%d", &a);
		add_edge(s, i, a);
		sum += a;
	}
	for(int i = 1; i <= n; i++)
	{
		int b;
		scanf("%d", &b);
		add_edge(i, t, b);
		sum += b;
	}
	scanf("%d", &m);
	for(int i = 1; i <= m; i++)
	{
		int x = ++cnt;
		int _x = ++cnt;
		int k;
		scanf("%d", &k);
		int c1, c2;
		scanf("%d%d", &c1, &c2);
		add_edge(s, x, c1);
		add_edge(_x, t, c2);
		sum += c1 + c2;
		for(int j = 1; j <= k; j++)
		{
			int a;
			scanf("%d", &a);
			add_edge(x, a, INF);
			add_edge(a, _x, INF);
		}
	}
	printf("%d", sum - run());
	return 0;
}
