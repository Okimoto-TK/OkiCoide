#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>
#define INF 0x3f3f3f3f
int head[10005];
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
} e[1000005];
int n, m, ptr, s, t;
int a[105][105];
const int dx[] = {0, 1, 0};
const int dy[] = {0, 0, 1};
inline void add_edge(int a, int b, int c, int _c)
{
	e[ptr] = edge(a, b, c);
	head[a] = ptr++;
	e[ptr] = edge(b, a, _c);
	head[b] = ptr++;
}
inline bool check(int x, int y)
{
	return x >= 1 && x <= n && y >= 1 && y <= m;
}
inline int getId(int x, int y)
{
	return (x - 1) * m + y;
}
int dep[10005];
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
int cur[10005];
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
		memcpy(cur, head, sizeof(head));
		ans += dfs(s, INF);
	}
	return ans;
}
int main()
{
	memset(head, -1, sizeof(head));
	scanf("%d%d", &n, &m);
	s = n * m + 1;
	t = s + 1;
	for(int i = 1; i <= n; i++)
	{
		for(int j = 1; j <= m; j++)
		{;
			scanf("%d", &a[i][j]);
			if(a[i][j] == 1) add_edge(s, getId(i, j), INF, 0);
			else if(a[i][j] == 2) add_edge(getId(i, j), t, INF, 0);
			for(int k = 1; k <= 2; k++)
			{
				int x = i - dx[k];
				int y = j - dy[k];
				if(check(x, y))
				{
					if(a[x][y] == a[i][j] && a[i][j] != 0)
					{
						add_edge(getId(x, y), getId(i, j), INF, INF);
					}
					else
					{
						add_edge(getId(x, y), getId(i, j), 1, 1);		
					}
				}
			}
		}
	}
	printf("%d", run());
	return 0;
}
