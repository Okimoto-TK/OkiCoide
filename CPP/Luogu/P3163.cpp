#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>
#define INF 0x3f3f3f3f
int head[100];
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
} e[1000000];
int n, ptr, s, t;
int a1, a2, an;
int b1, b2, bn;
char a[100][100];
inline void add_edge(int a, int b, int c, int _c)
{
	e[ptr] = edge(a, b, c);
	head[a] = ptr++;
	e[ptr] = edge(b, a, _c);
	head[b] = ptr++;
}
int dep[100];
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
int cur[100];
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
	while(scanf("%d", &n) != EOF)
	{
		memset(head, -1, sizeof(head));
		ptr = 0;
		scanf("%d%d%d%d%d%d", &a1, &a2, &an, &b1, &b2, &bn);
		a1++;
		a2++;
		b1++;
		b2++;
		s = n + 1;
		t = s + 1;
		add_edge(s, a1, an, 0);
		add_edge(a2, t, INF, 0);
		add_edge(s, b1, bn, 0);
		add_edge(b2, t, INF, 0);
		for(int i = 1; i <= n; i++)
		{
			scanf("%s", a[i] + 1);
		}
		for(int i = 1; i <= n; i++)
		{
			for(int j = 1; j < i; j++)
			{
				if(a[i][j] == 'N')
				{
					add_edge(i, j, INF, INF);
				}
				else if(a[i][j] == 'O')
				{
					add_edge(i, j, 1, 1);
				}
			}
		}
		if(run() != an + bn)
		{
			printf("No\n");
			continue;
		}
		memset(head, -1, sizeof(head));
		ptr = 0;
		add_edge(s, a1, an, 0);
		add_edge(a2, t, INF, 0);
		add_edge(s, b2, bn, 0);
		add_edge(b1, t, INF, 0);
		for(int i = 1; i <= n; i++)
		{
			for(int j = 1; j < i; j++)
			{
				if(a[i][j] == 'N')
				{
					add_edge(i, j, INF, INF);
				}
				else if(a[i][j] == 'O')
				{
					add_edge(i, j, 1, 1);
				}
			}
		}
		printf("%s\n", run() == an + bn ? "Yes" : "No");
	}
	return 0;
}
