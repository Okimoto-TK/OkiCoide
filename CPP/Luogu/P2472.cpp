#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>
#define INF 0x3f3f3f3f
int head[1000];
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
int r, c, d;
int s, t;
int ptr;
int a[30][30];
char b[30][30];
inline void add_edge(int a, int b, int c)
{
	e[ptr] = edge(a, b, c);
	head[a] = ptr++;
	e[ptr] = edge(b, a, 0);
	head[b] = ptr++;
}
inline int getId(int x, int y)
{
	return (x - 1) * c + y;
}
inline bool check(int x, int y)
{
	if(x >= 1 && x <= r && y >= 1 && y <= c) return true;
	return false;
}
int dep[1000];
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
int cur[1000];
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
int main()
{
	memset(head, -1, sizeof(head));
	scanf("%d%d%d", &r, &c, &d);
	for(int i = 1; i <= r; i++)
	{
		for(int j = 1; j <= c; j++)
		{
			scanf("%1d", &a[i][j]);
		}
	}
	for(int i = 1; i <= r; i++)
	{
		scanf("%s", b[i] + 1);
	}
	s = 2 * r * c + 1;
	t = s + 1;
	for(int i = 1; i <= r; i++)
	{
		for(int j = 1; j <= d; j++)
		{
			add_edge(getId(i, std::min(j, c)) + r * c, t, INF);
			add_edge(getId(i, std::max(c - j + 1, 1)) + r * c, t, INF);
		}
	}
	for(int i = 1; i <= c; i++)
	{
		for(int j = 1; j <= d; j++)
		{
			add_edge(getId(std::min(j, r), i) + r * c, t, INF);
			add_edge(getId(std::max(r - j + 1, 1), i) + r * c, t, INF);
		}
	}
	for(int i = 1; i <= r; i++)
	{
		for(int j = 1; j <= c; j++)
		{
			add_edge(getId(i, j), getId(i, j) + r * c, a[i][j]);
		}
	}
	int sum = 0;
	for(int i = 1; i <= r; i++)
	{
		for(int j = 1; j <= c; j++)
		{
			if(b[i][j] == 'L')
			{
				add_edge(s, getId(i, j), 1);
				sum++;	
			}
		}
	}
	for(int i = 1; i <= r; i++)
	{
		for(int j = 1; j <= c; j++)
		{
			for(int x = i - d; x <= i + d; x++)
			{
				for(int y = j - d; y <= j + d; y++)
				{
					if((x - i) * (x - i) + (y - j) * (y - j) > d * d) continue;
					if(check(x, y) && a[x][y] > 0)
					{
						add_edge(getId(i, j) + r * c, getId(x, y), INF);
						add_edge(getId(x, y) + r * c, getId(i, j), INF);
					}
				}
			}
		}
	}
	printf("%d", sum-run());
	return 0;
}
