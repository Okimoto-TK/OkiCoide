#include <cstdio>
#include <cstring>
#include <queue>
int head[305];
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
} e[100005];
int n, m;
int cnt, ptr;
int s, t;
int cur[305];
int dep[305];
void add_edge(int a, int b, int c, int _c)
{
	e[ptr] = edge(a, b, c);
	head[a] = ptr++;
	e[ptr] = edge(b, a, _c);
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
		ans += dfs(s, 0x7f7f7f7f);
	}
	return ans;
}
int main()
{
	for(scanf("%d%d", &n, &m); n != 0 || m != 0; scanf("%d%d", &n, &m))
	{
		memset(head, -1, sizeof(head));
		ptr = 0;
		cnt = n;
		s = ++cnt;
		t = ++cnt;
		for(int i = 1; i <= n; i++)
		{
			int c;
			scanf("%d", &c);
			if(c == 1)
			{
				add_edge(s, i, 1, 0);
			}
			else
			{
				add_edge(i, t, 1, 0);
			}
		}
		for(int i = 1; i <= m; i++)
		{
			int a, b;
			scanf("%d%d", &a, &b);
			add_edge(a, b, 1, 1);
		}
		printf("%d\n", run());
	}
	return 0;
}

