#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>
#include <algorithm>
int head[100005];
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
} e[400005];
int n, s, t;
int ptr;
std::vector<std::pair<int, int> > g[100005];
inline void add_edge(int a, int b, int c)
{
	e[ptr] = edge(a, b, c);
	head[a] = ptr++;
	e[ptr] = edge(b, a, 0);
	head[b] = ptr++;
}
void dfs1(int u, int fa)
{
	int len = g[u].size();
	bool vis = false;
	for(int i = 0; i < len; i++)
	{
		int v = g[u][i].first;
		int w = g[u][i].second;
		if(v == fa) continue;
		vis = true;
		add_edge(u, v, w);
		dfs1(v, u);
	}
	if(!vis)
	{
		add_edge(u, t, 0x3f3f3f3f);
	}
}
int dep[100005];
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
			if(dep[v] == 0 && e[i].f)
			{
				dep[v] = dep[u] + 1;
				q.push(v);
				if(v == t) break;
			}
		}
	}
	return dep[t] != 0;
}
int cur[100005];
int dfs2(int u, int f)
{
	if(u == t) return f;
	int fsum = 0;
	for(int i = cur[u]; i != -1; i = e[i].nxt)
	{
		int v = e[i].v;
		if(dep[v] == dep[u] + 1 && e[i].f > 0)
		{
			int _f = dfs2(v, std::min(f, e[i].f));
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
		ans += dfs2(s, 0x3f3f3f3f);
	}
	return ans;
}
int main()
{
	memset(head, -1, sizeof(head));
	scanf("%d%d", &n, &s);
	t = n + 1;
	for(int i = 1; i < n; i++)
	{
		int a, b, c;
		scanf("%d%d%d", &a, &b, &c);
		g[a].push_back(std::make_pair(b, c));
		g[b].push_back(std::make_pair(a, c));
	}
	dfs1(s, 0);
	printf("%d", run());
	return 0;
}
