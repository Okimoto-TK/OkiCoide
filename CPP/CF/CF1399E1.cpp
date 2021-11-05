#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>
struct Edge
{
	int v, c;
	long long w;
	Edge() { v = w = 0; }
	Edge(int a, long long b)
	{
		v = a;
		w = b;
		c = 1;
	}
	Edge(int a, long long b, int x)
	{
		v = a;
		w = b;
		c = x;
	}
	bool operator< (const Edge & e) const
	{
		return (w - w / 2) * c < (e.w - e.w / 2) * e.c;
	}
};
int t, n;
long long S, cnt;
int size[100005];
std::vector<Edge> vec[100005];
std::priority_queue<Edge, std::vector<Edge>, std::less<Edge> > q; 
void init()
{
	cnt = 0;
	while(!q.empty()) q.pop();
	memset(size, 0, sizeof(size));
	for(int i = 0; i <= 100000; i++)
	{
		vec[i].clear();
	}
}
void addEdge(int a, int b, long long w)
{
	vec[a].push_back(Edge(b, w));
	vec[b].push_back(Edge(a, w));
}
void dfs(int u, int fa)
{
	int len = vec[u].size();
	size[u] = 0;
	bool leaf = true;
	for(int i = 0; i < len; i++)
	{
		if(vec[u][i].v == fa) continue;
		leaf = false;
		dfs(vec[u][i].v, u);
		q.push(Edge(vec[u][i].v, vec[u][i].w, size[vec[u][i].v]));
		cnt += vec[u][i].w * size[vec[u][i].v];
		size[u] += size[vec[u][i].v];
	}
	if(leaf) size[u] = 1;
}

int main()
{
	for(scanf("%d", &t); t != 0; t--)
	{
		init();
		scanf("%d%lld", &n, &S);
		for(int i = 1; i < n; i++)
		{
			int v, u;
			long long w;
			scanf("%d%d%lld", &v, &u, &w);
			addEdge(v, u, w);
		}
		dfs(1, 0);
		int ans = 0;
		while(cnt > S)
		{
			Edge x = q.top();
			q.pop();
			long long _w = x.w / 2;
			long long diff = x.w * x.c  - _w * x.c;
			cnt -= diff;
			q.push(Edge(x.v, _w, x.c));
			ans++;
		}
		printf("%d\n", ans);
	}
	return 0;
}
