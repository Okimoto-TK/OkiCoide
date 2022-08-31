#include <cstdio>
#include <cstring>
#define N 100000
#define M 63
int tot;
int head[N + 5];
struct Edge
{
	int v, nxt;
	long long w;
} e[N * 2 + 5];
struct Bas
{
	long long bas[64];
	void insert(long long x)
	{
		for(int d = M; d >= 0; d--)
		{
			if(x & (1ll << d))
			{
				if(bas[d] == 0)
				{
					bas[d] = x;
					break;
				}
				else
				{
					x ^= bas[d];
				}
			}
		}
	}
	long long query(long long ans)
	{
		for(int d = M; d >= 0; d--)
		{
			if((ans ^ bas[d]) > ans)
			{
				ans ^= bas[d];
			}
		}
		return ans;
	}
} B;
void add_Edge(int u, int v, long long w)
{
	e[tot].v = v;
	e[tot].w = w;
	e[tot].nxt = head[u];
	head[u] = tot++;
}
int n, m;
bool vis[N + 5];
long long sum[N + 5];
long long loop[10 * N + 5];
long long val = -1;
int cnt = 0;
void dfs(int u)
{
	if(val == -1 && u == n) val = sum[u];
	for(int i = head[u]; i != -1; i = e[i].nxt)
	{
		if(!vis[e[i].v])
		{
			vis[e[i].v] = true;
			sum[e[i].v] = sum[u] ^ e[i].w;
			dfs(e[i].v);
		}
		else
		{
			loop[++cnt] = sum[u] ^ e[i].w ^ sum[e[i].v];
		}
	}
}
int main()
{
	memset(head, -1, sizeof(head));
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= m; i++)
	{
		int s, t;
		long long d;
		scanf("%d%d%lld", &s, &t, &d);
		add_Edge(s, t, d);
		add_Edge(t, s, d);
	}
	vis[1] = true;
	sum[1] = 0;
	dfs(1);
	for(int i = 1; i <= cnt; i++)
	{
		B.insert(loop[i]);
	}
	printf("%lld", B.query(val));
	return 0;
}