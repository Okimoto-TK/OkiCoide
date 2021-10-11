#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>
int head[1105];
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
} e[500005];
int n, b;
int s, t;
int ptr;
int p[1005][25];
int c[25];
inline void add_edge(int a, int b, int c)
{
	e[ptr] = edge(a, b, c);
	head[a] = ptr++;
	e[ptr] = edge(b, a, 0);
	head[b] = ptr++;
}
int dep[1105];
inline bool bfs()
{
	for(int i = 1; i <= n + b + 2; i++) dep[i] = 0;
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
int cur[1105];
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
			int _f = dfs(v, std::min(e[i].f, f));
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
		for(int i = 1; i <= n + b + 2; i++) cur[i] = head[i];
		ans += dfs(s, 0x7f7f7f7f);
	}
	return ans;
}
inline bool check(int x)
{
	for(int k = 1; k + x - 1 <= b; k++)
	{
		for(int i = 1; i <= n + b + 2; i++) head[i] = -1;
		ptr = 0;
		for(int i = 1; i <= n; i++)
		{
			add_edge(s, i, 1);
		}
		for(int i = 1; i <= b; i++)
		{
			add_edge(i + n, t, c[i]);
		}
		for(int i = 1; i <= n; i++)
		{
			for(int j = k; j <= k + x - 1; j++)
			{
				add_edge(i, p[i][j] + n, 1);
			}
		}
		if(run() == n) return true;
	}
	return false;
}
int main()
{
	scanf("%d%d", &n, &b);
	s = n + b + 1;
	t = n + b + 2;
	for(int i = 1; i <= n; i++)
	{
		for(int j = 1; j <= b; j++)
		{
			scanf("%d", &p[i][j]);
		}
	}
	for(int i = 1; i <= b; i++)
	{
		scanf("%d", &c[i]);
	}
	int l = 1;
	int r = b;
	while(l < r)
	{
		int mid = (l + r) >> 1;
		if(check(mid))
		{
			r = mid;
		}
		else
		{
			l = mid + 1;
		}
	}
	printf("%d", l);
	return 0;
}
