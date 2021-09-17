#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>
int head[1005];
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
} e[1000005];
int _s, n, m, ptr, s, t;
int a[105];
int b[105];
int c[105];
int d[105];
int cn;
int dn;
bool win[6][6] = {
	{false, false, false, false, false, false}, 
	{false, false, false, false, true, true},
	{false, true, false, false, false, true},
	{false, true, true, false, false, false},
	{false, false, true, true, false, false},
	{false ,false, false, true, true, false}
};
int get_id(char x)
{
	if(x == 'W') return 1;
	if(x == 'H') return 2;
	if(x == 'J') return 3;
	if(x == 'Y') return 4;
	return 5;
}
void add_edge(int a, int b, int c)
{
	e[ptr] = edge(a, b, c);
	head[a] = ptr++;
	e[ptr] = edge(b, a, 0);
	head[b] = ptr++;
}
int dep[1005];
bool bfs()
{
	memset(dep, 0, sizeof(dep));
	dep[_s] = 1;
	std::queue<int> q;
	q.push(_s);
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
int cur[1005];
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
int run()
{
	int ans = 0;
	while(bfs())
	{
		memcpy(cur, head, sizeof(cur));
		ans += dfs(_s, 0x3f3f3f3f);
	}
	return ans;
}
int main()
{
	memset(head, -1, sizeof(head));
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++)
	{
		char s[5];
		scanf("%s", s);
		c[i] = get_id(s[0]);
		if(c[i] == 4) cn++;
	}
	for(int i = 1; i <= n; i++)
	{
		char s[5];
		scanf("%s", s);
		d[i] = get_id(s[0]);
		if(d[i] == 5) dn++;
	}
	for(int i = 1; i <= n; i++)
	{
		int x;
		scanf("%d", &x);
		a[i] = x;
	}
	for(int i = 1; i <= n; i++)
	{
		int x;
		scanf("%d", &x);
		b[i] = x;
	}
	s = 2 * n + 1;
	t = s + 1;
	_s = t + 1;
	add_edge(_s, s, m);
	for(int i = 1; i <= n; i++)
	{
		add_edge(s, i, a[i] + (c[i] == 3 ? 1 : 0) * cn);
		add_edge(i + n, t, b[i] + (d[i] == 3 ? 1 : 0) * dn);
	}
	for(int i = 1; i <= n; i++)
	{
		for(int j = 1; j <= n; j++)
		{
			if(win[c[i]][d[j]]) add_edge(i, j + n, 1);
		}
	}
	printf("%d", run());
	return 0;
}
