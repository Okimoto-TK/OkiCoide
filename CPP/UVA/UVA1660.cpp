#include <cstdio>
#include <cstring>
#include <cctype>
#include <queue>
#include <algorithm>
#define INF 0x3f3f3f3f
int read()
{
	int s = 0, f = 1;
	char ch = getchar();
	while(!isdigit(ch)) {
		if(ch == '-') f = -1;
		ch = getchar();
	}
	while(isdigit(ch)) {
		s = s * 10 + ch - '0';
		ch = getchar();
	}
	return s * f;
}
int T;
int head[400];
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
} e[160000];
int n, m, s, t, ptr;
bool g[100][100];
inline void add_edge(int a, int b, int c)
{
	e[ptr] = edge(a, b, c);
	head[a] = ptr++;
	e[ptr] = edge(b, a, 0);
	head[b] = ptr++;
}
int dep[400];
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
				if(v == t) break;
				q.push(v);
			}
		}
	}
	return dep[t] != 0;
}
int cur[400];
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
inline int run()
{
	int ans = 0;
	while(bfs())
	{
		memcpy(cur, head, sizeof(cur));
		ans += dfs(s, INF);
	}
	return ans;
}
int main()
{
	while(scanf("%d", &n) != EOF)
	{
		memset(g, 0, sizeof(g));
		scanf("%d", &m);
		for(int i = 1; i <= m; i++)
		{
			int u = read();
			int v = read();
			g[++u][++v] = true;
			g[v][u] = true;
		}
		if(n <= 1)
		{
			printf("%d\n", n);
			continue;
		}
		int ans = INF;
		for(int i = 1; i <= n; i++)
		{
			for(int j = 1; j <= n; j++)
			{
				if(i == j) continue;
				memset(head, -1, sizeof(head));
				ptr = 0;
				s = i + n;
				t = j;
				for(int u = 1; u <= n; u++)
				{
					for(int v = u + 1; v <= n; v++)
					{
						if(!g[u][v]) continue;
						add_edge(u + n, v, INF);
						add_edge(v + n, u, INF);
					}
					add_edge(u, u + n, 1);
				}
				ans = std::min(ans, run());
			}
		}
		printf("%d\n", ans == INF ? n : ans);
	}
	return 0;
}
