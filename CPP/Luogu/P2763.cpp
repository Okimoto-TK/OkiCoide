#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>
#define INF 0x3f3f3f3f
int head[1100];
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
} e[1000000];
int k, n, s, t, ptr;
inline void add_edge(int a, int b, int c)
{
	e[ptr] = edge(a, b, c);
	head[a] = ptr++;
	e[ptr] = edge(b, a, 0);
	head[b] = ptr++;
}
int dep[1100];
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
int cur[1100];
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
		ans += dfs(s, INF);
	}
	return ans;
}
std::queue<int> ans[25];
inline void get()
{
	for(int i = 1; i <= n; i++)
	{
		for(int j = head[i]; j != -1; j = e[j].nxt)
		{
			int v = e[j].v;
			if(v == s) continue;
			if(e[j].f == 0) ans[e[j].v - n].push(i);
		}
	}
}
int main()
{
	int m = 0;
	memset(head, -1, sizeof(head));
	scanf("%d%d", &k, &n);
	s = k + n + 1;
	t = s + 1;
	for(int i = 1; i <= k; i++)
	{
		int r;
		scanf("%d", &r);
		m += r;
		add_edge(i + n, t, r);
	}
	for(int i = 1; i <= n; i++)
	{
		add_edge(s, i, 1);
		int p;
		scanf("%d", &p);
		for(int j = 1; j <= p; j++)
		{
			int r;
			scanf("%d", &r);
			add_edge(i, r + n, 1);
		}
	}
	if(run() == m)
	{
		get();
		for(int i = 1; i <= k; i++)
		{
			printf("%d: ", i);
			while(!ans[i].empty())
			{
				printf("%d ", ans[i].front());
				ans[i].pop();
			}
			putchar('\n');
		}
	}
	else
	{
		printf("No Solution!");
	}
	return 0;
}
