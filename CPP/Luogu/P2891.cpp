#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>
#define INF 0x7f7f7f7f
int head[2005];
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
} e[6000005];
int n, f, d, s, t;
int ptr, cnt;
int dep[2005];
int cur[2005];
void add_edge(int a, int b, int c)
{
	e[ptr] = edge(a, b, c);
	head[a] = ptr++;
	e[ptr] = edge(b, a, 0);
	head[b] = ptr++;
}
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
int get()
{
	int cnt = 0;
	for(int i = 1; i <= n; i++)
	{
		for(int j = head[i]; j != -1; j = e[j].nxt)
		{
			if(e[j].v == s) continue;
			if(e[j].f == 0) cnt++;
		}
	}
	return cnt;
}
int main()
{
	memset(head, -1, sizeof(head));
	scanf("%d%d%d", &n, &f, &d);
	cnt = n;
	s = ++cnt;
	t = ++cnt;
	for(int i = 1; i <= f; i++) add_edge(s, ++cnt, 1);
	for(int i = 1; i <= d; i++) add_edge(++cnt, t, 1);
	for(int i = 1; i <= n; i++)
	{
		int x = ++cnt;
		int y = ++cnt;
		int fi, di;
		scanf("%d%d", &fi, &di);
		for(int j = 1; j <= fi; j++)
		{
			int a;
			scanf("%d", &a);
			add_edge(a + n + 2, x, 1);
		}
		for(int j = 1; j <= di; j++)
		{
			int a;
			scanf("%d", &a);
			add_edge(y, a + n + 2 + f, 1);				
		}
		add_edge(x, i, 1);
		add_edge(i, y, 1);
	}
	printf("%d", run());
	return 0;
}
