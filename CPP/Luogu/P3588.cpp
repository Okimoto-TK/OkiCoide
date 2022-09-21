#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#define N 100000
#define B 400000
int n, s, m, pool;
int a[N + 5];
int deg[N * 10 + 5];
bool able[N * 10 + 5];
struct Edge
{
	int v, w;
	Edge()
	{
		v = w = 0;
	}
	Edge(int _v)
	{
		v = _v;
		w = 0;
	}
	Edge(int _v, int _w)
	{
		v = _v;
		w = _w;
	}
};
std::vector<Edge> vec[N * 12 + 5];
void buildin(int k, int l, int r)
{
	able[k] = true;
	if(l == r)
	{
		vec[k].push_back(Edge(l + B));
		deg[l + B]++;
		return;
	}
	int mid = (l + r) >> 1;
	vec[k].push_back(Edge(k << 1));
	deg[k << 1]++;
	vec[k].push_back(Edge(k << 1 | 1));
	deg[k << 1 | 1]++;
	buildin(k << 1, l, mid);
	buildin(k << 1 | 1, mid + 1, r);
}
void buildout()
{
	for(int i = 1; i <= n; i++)
	{
		able[i + B] = true;
	}
}
void changein(int k, int l, int r, int x, int y, int v)
{
	if(x <= l && r <= y)
	{
		vec[v].push_back(Edge(k));
		deg[k]++;
		return;
	}
	int mid = (l + r) >> 1;
	if(x <= mid) changein(k << 1, l, mid, x, y, v);
	if(y > mid) changein(k << 1 | 1, mid + 1, r, x, y, v);
}
void add(int a, int k)
{
	vec[a + B].push_back(Edge(k, 1));
	deg[k]++;
}
void add(int b, int c, int k)
{
	changein(1, 1, n, b, c, k);
}
std::queue<int> q;
int vis[N * 10 + 5];
int val[N * 10 + 5];
bool bfs()
{
	int aim = 0;
	for(int i = 1; i <= 10 * N; i++)
	{
		val[i] = 1e9;
		if(able[i] && deg[i] == 0)
		{
			q.push(i);
		}
		aim += able[i];
	}
	int cnt = 0;
	while(!q.empty())
	{
		int u = q.front();
		q.pop();
		//printf("%d\n", u);
		if(vis[u]) continue;
		vis[u] = true;
		cnt++;
		for(auto v : vec[u])
		{
			//printf("--%d %d\n", v.v, deg[v.v]);
			val[v.v] = std::min(val[v.v], val[u] - v.w);
			
			if(v.v >= B && v.v <= N + B && a[v.v - B] > 0)
			{
				//printf("%d %d\n", v.v, val[v.v]);
				if(a[v.v - B] > val[v.v])
				{
					return false;
				}
				val[v.v] = a[v.v - B];
			}
			if(val[v.v] <= 0) return false;
			if(--deg[v.v] == 0)
			{
				q.push(v.v);
			}
		}
	}
	//printf("%d %d\n", cnt, aim);
	return cnt == aim;
}
int main()
{
	scanf("%d%d%d", &n, &s, &m);
	for(int i = 1; i <= s; i++)
	{
		int p, d;
		scanf("%d%d", &p, &d);
		a[p] = d;
	}
	buildin(1, 1, n);
	buildout();
	for(int i = 1; i <= m; i++)
	{
		able[i + 2 * B] = true;
		int l, r, k;
		scanf("%d%d%d", &l, &r, &k);
		int last = l;
		for(int j = 1; j <= k; j++)
		{
			int x;
			scanf("%d", &x);
			if(x != last)
			{
				add(last, x - 1, i + 2 * B);
			}
			add(x, i + 2 * B);
			last = x + 1;
		}
		if(last <= r)
		{
			add(last, r, i + 2 * B);
		}
	}
	if(bfs())
	{
		printf("TAK\n");
		for(int i = 1; i <= n; i++)
		{
			printf("%d ", val[i + B]);
		}
	}
	else
	{
		printf("NIE");
		return 0;
	}
	return 0;
}
