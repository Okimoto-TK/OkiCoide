#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <queue>
int head[205];
struct E
{
	int u, v, f;
	int nxt;
	E() { u = v = f = nxt = -1; }
	E(int a, int b, int c)
	{
		u = a;
		v = b;
		f = c;
		nxt = head[u];
	}
} edge[4005];
int ptr;
int n, m, x;
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
		d[1] = 2147483647;
		std::queue<int> q;
		q.push(1);
		while(!q.empty())
		{
			int u = q.front();
			q.pop();
			for(int i = head[u]; i != -1; i = edge[i].nxt)
			{
				if(d[edge[i].v] == 0 && edge[i].f > 0)
				{
					q.push(edge[i].v);
					d[edge[i].v] = std::min(d[u], edge[i].f);
					tr[edge[i].v] = i;
				}
			}
			if(d[n] != 0) break;
		}
		if(d[n] == 0) break;
		for(int i = n; i != 1; i = edge[tr[i]].u)
		{
			edge[tr[i]].f -= d[n];
			edge[tr[i] ^ 1].f += d[n];
		}
		ans += d[n];
	}
	return ans;
}
int main()
{
	for(int i = 0; i <= 200; i++) head[i] = -1; 
	scanf("%d%d%d", &n, &m, &x);
	for(int i = 1; i <= m; i++)
	{
		int a, b, c;
		scanf("%d%d%d", &a, &b, &c);
		add_edge(a, b, c);
	}
	int ans = bfs();
	if(ans == 0)
	{
		printf("Orz Ni Jinan Saint Cow!");
		return 0;
	}
	printf("%d %d", ans, (int)ceil(double(x) / double(ans)));
	return 0;
}
