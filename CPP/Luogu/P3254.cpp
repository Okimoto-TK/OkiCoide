#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>
int head[500];
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
} e[100000];
int m, n, s, t, sum, ptr;
inline void add_edge(int a, int b, int c)
{
	e[ptr] = edge(a, b, c);
	head[a] = ptr++;
	e[ptr] = edge(b, a, 0);
	head[b] = ptr++;
}
int dep[500];
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
int cur[500];
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
void run()
{
	int ans = 0;
	while(bfs())
	{
		memcpy(cur, head, sizeof(head));
		ans += dfs(s, 0x3f3f3f3f);
	}
	if(ans != sum)
	{
		printf("0");
		return;
	}
	printf("1\n");
	for(int i = 1; i <= m; i++)
	{
		for(int j = head[i]; j != -1; j = e[j].nxt)
		{
			if(e[j].v == s) continue;
			if(e[j].f == 0) printf("%d ", e[j].v - m);
		}
		putchar('\n');
	}
}
int main()
{
	memset(head, -1, sizeof(head));
	scanf("%d%d", &m, &n);
	s = m + n + 1;
	t = s + 1;
	for(int i = 1; i <= m; i++)
	{
		int r;
		scanf("%d", &r);
		sum += r;
		add_edge(s, i, r);
	}
	for(int i = 1; i <= n; i++)
	{
		int c;
		scanf("%d", &c);
		add_edge(i + m, t, c);
	}
	for(int i = 1;i <= m; i++)
	{
		for(int j = 1; j <= n; j++)
		{
			add_edge(i, j + m, 1);
		}
	}
	run();
	return 0;
}
