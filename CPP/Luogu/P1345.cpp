#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>
int n, m, s, t;
int head[205];
struct E
{
	int u, v, f, nxt;
	E() { u = v = f = nxt = -1; }
	E(int a, int b, int c)
	{
		u = a;
		v = b;
		f = c;
		nxt = head[a];
	}
} edge[5005];
int ptr;
inline void add_edge(int a, int b, int c)
{
	edge[ptr] = E(a, b, c);
	head[a] = ptr++;
	edge[ptr] = E(b, a, 0);
	head[b] = ptr++;
}
int d[205];
int tr[205];
int bfs()
{
	int ans = 0;
	while(true)
	{
		memset(d, 0, sizeof(d));
		d[s + n] = 1;
		std::queue<int> q;
		q.push(s + n);
		while(!q.empty())
		{
			int u = q.front();
			q.pop();
			for(int i = head[u]; i != -1; i = edge[i].nxt)
			{
				int v = edge[i].v;
				if(d[v] == 0 && edge[i].f > 0)
				{
					q.push(v);
					tr[v] = i;
					d[v] = std::min(d[u], edge[i].f);
				}
			}
			if(d[t] != 0) break;
		}
		if(d[t] == 0) break;
		for(int i = t; i != s + n; i = edge[tr[i]].u)
		{
			edge[tr[i]].f -= d[t];
			edge[tr[i] ^ 1].f += d[t];
		}
		ans += d[t];
	}
	return ans;
}
int main()
{
	for(int i = 1; i <= 200; i++) head[i] = -1;
	scanf("%d%d%d%d", &n, &m, &s, &t);
	for(int i = 1; i <= n; i++) add_edge(i, i + n, 1);
	for(int i = 1; i <= m; i++)
	{
		int a, b;
		scanf("%d%d", &a, &b);
		add_edge(a + n, b, 2147483647);
		add_edge(b + n, a, 2147483647);
	}
	printf("%d", bfs());
	return 0;
}
