#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>
#define INF 0x7f7f7f7f
#define int long long
int head[1005];
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
} e[200005];
int n, m;
int ptr;
int s, t;
int cur[1005];
int dep[1005];
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
				if(v == t + n) break;
			}		
		}
	}
	return dep[t + n] != 0;
}
int dfs(int u, int f)
{
	if(u == t + n) return f;
	int fsum = 0;
	for(int i = cur[u]; i != -1; i = e[i].nxt)
	{
		int v = e[i].v;
		if(dep[v] == dep[u] + 1 && e[i].f > 0)
		{
			int _f = dfs(v, std::min(f, e[i].f));
			e[i].f -=  _f;
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
bool vis[1005];
std::queue<int> ans;
void get()
{
	std::queue<int> q;
	q.push(s);
	vis[s] = true;
	while(!q.empty())
	{
		int u = q.front();
		q.pop();
		for(int i = head[u]; i != -1; i = e[i].nxt)
		{
			if(e[i].f > 0 && !vis[e[i].v])
			{
				vis[e[i].v] = true;
				q.push(e[i].v);
			}
		}
	}
	for(int i = 1; i <= n; i++)
	{
		if(vis[i] && !vis[i + n]) ans.push(i);
	}
}
signed main()
{
	memset(head, -1ll, sizeof(head));
	scanf("%lld%lld", &n, &m);
	scanf("%lld%lld", &s, &t);
	for(int i = 1; i <= n; i++)
	{
		int c;
		scanf("%lld", &c);
		add_edge(i, i + n, c);
	}
	for(int i = 1; i <= m; i++)
	{
		int x, y;
		scanf("%lld%lld", &x, &y);
		add_edge(x + n, y, INF);
		add_edge(y + n, x, INF);
	}
	run();
	get();
	while(!ans.empty())
	{
		printf("%lld ", ans.front());
		ans.pop();
	}
	return 0;
}
