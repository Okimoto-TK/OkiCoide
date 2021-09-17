#include <cstdio>
#include <cstring>
#include <queue>
#define N 105
#define int long long
int head[N];
struct edge
{
	int u, v, w, nxt;
	edge() { u = v = w = nxt = -1; }
	edge(int a, int b, int c)
	{
		u = a;
		v = b;
		w = c;
		nxt = head[a];
	}
} e[10005];
int n, p, ptr;
int ind[N];
int _ind[N];
int c[N];
int d[N];
inline void add_edge(int a, int b, int c)
{
	e[ptr] = edge(a, b, c);
	head[a] = ptr++;
}
signed main()
{
	memset(head, -1, sizeof(head));
	scanf("%lld%lld", &n, &p);
	for(int i = 1; i <= n; i++)
	{
		scanf("%lld%lld", &c[i], &d[i]);
	}
	for(int i = 1; i <= p; i++)
	{
		int u, v, w;
		scanf("%lld%lld%lld", &u, &v, &w);
		ind[v]++;
		_ind[v]++;
		add_edge(u, v, w);
	}
	std::queue<int> q;
	for(int i = 1; i <= n; i++)
	{
		if(ind[i] == 0)
		{
			q.push(i);
		}
	}
	while(!q.empty())
	{
		int u = q.front();
		q.pop();
		if(_ind[u] != 0) c[u] -= d[u];
		if(c[u] <= 0) continue;
		for(int i = head[u]; i != -1; i = e[i].nxt)
		{
			int v = e[i].v;
			c[v] += e[i].w * c[u];
			if(--ind[v] == 0)
			{
				q.push(v);
			}
		}		
	}
	bool non = true;
	for(int i = 1; i <= n; i++)
	{
		if(head[i] == -1 && c[i] > 0)
		{
			non = false;
			printf("%lld %lld\n", i, c[i]);
		}
		if(head[i] == -1 && c[i] < 0) non = false;
	}
	if(non) printf("NULL");
	return 0;
}
