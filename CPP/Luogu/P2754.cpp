#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>
int head[20000];
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
} e[4000000];
int n, m, k, ptr, s, t;
int f[100];
int c[100];
int d[100][100];
void add_edge(int a, int b, int c)
{
	e[ptr] = edge(a, b, c);
	head[a] = ptr++;
	e[ptr] = edge(b, a, 0);
	head[b] = ptr++;
}
int dep[20000];
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
				if(v == t) break;
			}
		}
	}
	return dep[t] != 0;
}
int cur[20000];
int dfs(int u, int flow)
{
	if(u == t) return flow;
	int fsum = 0;
	for(int i = cur[u]; i != -1; i = e[i].nxt)
	{
		cur[u] = i;
		int v = e[i].v;
		if(dep[v] == dep[u] + 1 && e[i].f > 0)
		{
			int _f = dfs(v, std::min(flow, e[i].f));
			flow -= _f;
			fsum += _f;
			e[i].f -= _f;
			e[i ^ 1].f += _f;
			if(flow <= 0) break;
		}
	}
	return fsum;
}
int run()
{
	int ans = 0;
	while(bfs())
	{
		memcpy(cur, head, sizeof(cur));
		ans += dfs(s, 0x3f3f3f3f);
	}
	return ans;
}
bool check(int x)
{
	memset(head, -1, sizeof(head));
	ptr = 0;
	s = 2;
	t = 1 + x * (n + 2);
	for(int i = 1; i <= x; i++)
	{
		for(int j = 1; j <= m; j++)
		{
			int ori = d[j][(i - 1) % c[j] + 1];
			int des = d[j][i % c[j] + 1];
			add_edge(ori + (i - 1) * (n + 2), des + i * (n + 2), f[j]);
		}
	}
	for(int i = 1; i <= n + 2; i++)
	{
		for(int j = 0; j < x; j++)
		{
			add_edge(i + j * (n + 2), i + (j + 1) * (n + 2), 0x3f3f3f3f);
		}
	}
	int ans = run();
	return ans >= k;
}
int main()
{
	scanf("%d%d%d", &n, &m, &k);
	for(int i = 1; i <= m; i++)
	{
		scanf("%d%d", &f[i], &c[i]);
		for(int j = 1; j <= c[i]; j++)
		{
			scanf("%d", &d[i][j]);
			d[i][j] += 2;
		}
	}
	int l = 1;
	int r = 1000;
	bool suc = false;
	while(l < r)
	{
		int mid = (l + r) >> 1;
		if(check(mid))
		{
			suc = true;
			r = mid;
		}
		else
		{
			l = mid + 1;
		}
	}
	if(suc) printf("%d", l);
	else printf("0");
	return 0;
}
