#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>
#define N 200000
int head[N];
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
} e[N << 4];
int n, k, s, t, ptr;
char con[100][100];
inline void add_edge(int a, int b, int c)
{
	e[ptr] = edge(a, b, c);
	head[a] = ptr++;
	e[ptr] = edge(b, a, 0);
	head[b] = ptr++;
}
int dep[N];
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
int cur[N];
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
		ans += dfs(s, 0x3f3f3f3f);
	}
	return ans;
}
bool check(int x)
{
	memset(head, -1, sizeof(head));
	ptr = 0;
	for(int i = 1; i <= n; i++)
	{
		add_edge(s, i, x);
		add_edge(i, i + n, x);
		add_edge(i, i + 2 * n, k);
		add_edge(i + 3 * n, t, x);
		add_edge(i + 4 * n, i + 3 * n, x);
		add_edge(i + 5 * n, i + 3 * n, k);
	}
	for(int i = 1; i <= n; i++)
	{
		for(int j = 1; j <= n; j++)
		{
			if(con[i][j] == 'Y') add_edge(i + n, j + 4 * n, 1);
			else add_edge(i + 2 * n, j + 5 * n, 1);
		}
	}
	return run() == n * x;
}
int main()
{
	scanf("%d%d", &n, &k);
	s = n * 6 + 1;
	t = n * 6 + 2;
	for(int i = 1; i <= n; i++)
	{
		scanf("%s", con[i] + 1);
	}
	int l = 0;
	int r = n;
	while(l < r)
	{
		int mid = (l + r + 1) >> 1;
		if(check(mid)) l = mid;
		else r = mid - 1;
	}
	printf("%d", l);
	return 0;
}
