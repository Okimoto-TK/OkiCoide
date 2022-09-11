#include <cstdio>
#include <queue>
#include <vector>
#include <algorithm>
#define N 500000
int read()
{
    int s = 0, w = 1;
    char ch = getchar();
    while(ch < '0' || ch > '9')
    {
        if(ch == '-') w = -1;
        ch = getchar();
    }
    while(ch >= '0' && ch <= '9')
    {
		s = s * 10 + ch - '0';
		ch = getchar();
	}
    return s * w;
}
void write(int a)
{
    if(a > 9) write(a / 10);
    putchar(a % 10 + '0');
}
struct Edge
{
	int u, v;
};
int n, m, pool;
bool vis[N + 5];
bool done[N + 5];
bool mint[N + 5];
Edge e[N + 5];
int fa[N + 5];
int dep[N + 5];
int idx[N + 5];
int s[N + 5];
std::priority_queue<int, std::vector<int>, std::greater<int> > h[N + 5];
int ans[N + 5];
struct Edg
{
	int id, v;
	Edg(int x, int y)
	{
		id = x, v = y;
	}
};
std::vector<Edg> g[N + 5];
void dfs1(int u, int f)
{
	fa[u] = f;
	dep[u] = dep[f] + 1;
	for(auto v : g[u])
	{
		if(v.v == f) continue;
		dfs1(v.v, u);
		idx[v.v] = v.id;
	}
}
int find(int x)
{
	if(x == s[x]) return x;
	return s[x] = find(s[x]);
}
void merge(int x, int y)
{
	int fx = find(x), fy = find(y);
	if(fx != fy)
	{
		s[fx] = fy;
	}
}
int count(int x, int y)
{
	//printf("-----\n");
	int res = 0;
	while(x != y)
	{
		//printf("%d %d\n", x, y);
		if(dep[x] < dep[y])
		{
			std::swap(x, y);
		}
		if(done[x])
		{
			x = find(x);
			continue;
		}
		if(!done[x]) res++;
		x = fa[x];
	}
	return res;
}
void modify(int x, int y, int v)
{
	while(x != y)
	{
		if(dep[x] < dep[y])
		{
			std::swap(x, y);
		}
		if(done[x])
		{
			x = find(x);
			continue;
		}
		h[v].push(idx[x]);
		done[x] = true;
		merge(x, fa[x]);
		x = find(x);
	}
}
int main()
{
	// freopen("in.in", "r", stdin);
	// freopen("out.out", "w", stdout);
	// scanf("%d%d", &n, &m);
	n = read();
	m = read();
	int root;
	for(int i = 1; i <= m; i++)
	{
		// scanf("%d%d", &e[i].u, &e[i].v);
		e[i].u = read();
		e[i].v = read();
		int c = read();
		// scanf("%d", &c);
		if(c == 1)
		{
			root = e[i].u;
			mint[i] = true;
			g[e[i].u].push_back(Edg(i, e[i].v));
			g[e[i].v].push_back(Edg(i, e[i].u));
		}
	}
	for(int i = 1; i <= n; i++) s[i] = i;
	dfs1(root, 0);
	for(int i = 1; i <= m; i++)
	{
		int a = e[i].u, b = e[i].v;
		if(mint[i])
		{
			int v = count(a, b);
			//printf("%d\n", v);
			if(v == 1)
			{
				modify(a, b, ++pool);
			}
			continue;
		}
		int v = count(a, b);
		//printf("%d\n", v);
		if(v != 0)
		{
			modify(a, b, pool + 1);
		}
		pool += v;
		ans[i] = ++pool;
	}
	for(int i = 1; i <= m; i++)
	{
		int j = 0;
		while(!h[i].empty())
		{
			int u = h[i].top();
			h[i].pop();
			ans[u] = i + (j++);
		}
	}
	for(int i = 1; i <= m; i++)
	{
		// printf("%d ", ans[i]);
		write(ans[i]);
		putchar(' ');
	}
	return 0;
}