#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>
int head[40005];
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
int n1, n2, n3;
int m1, m2;
int s, t;
int ptr;
inline void add_edge(int a, int b, int c)
{
	e[ptr] = edge(a, b, c);
	head[a] = ptr++;
	e[ptr] = edge(b, a, 0);
	head[b] = ptr++;
}
int dep[40005];
inline bool bfs()
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
int cur[40005];
int dfs(int u, int f)
{
	if(u == t) return f;
	int fsum = 0;
	for(int i = cur[u]; i != -1; i = e[i].nxt)
	{
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
inline int run()
{
	int ans = 0;
	while(bfs())
	{
		memcpy(cur, head, sizeof(head));
		ans += dfs(s, 0x3f3f3f3f);
	}
	return ans;
}
int main()
{
	memset(head, -1, sizeof(head));
	scanf("%d%d%d", &n1, &n2, &n3);
	s = n1 + n2 + n3 + n1 + 1;
	t = s + 1;
	for(int i = 1; i <= n2; i++)
	{
		add_edge(s, i, 1);
	}
	for(int i = n1 + n2 + n1 + 1; i <= n1 + n1 + n2 + n3; i++)
	{
		add_edge(i, t, 1);
	}
	scanf("%d", &m1);
	for(int i = 1; i <= m1; i++)
	{
		int x, y;
		scanf("%d%d", &x, &y);
		add_edge(y, x + n2, 1);
	}
	for(int i = n2 + n1 + 1; i <= n2 + n1 + n1; i++)
	{
		add_edge(i - n1, i, 1);
	}
	scanf("%d", &m2);
	for(int i = 1; i <= m2; i++)
	{
		int x, y;
		scanf("%d%d", &x, &y);
		add_edge(x + n2 + n1, y + n1 + n2 + n1, 1);
	}
	printf("%d", run());
	return 0;
}
