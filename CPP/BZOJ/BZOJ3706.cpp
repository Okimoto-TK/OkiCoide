#include <cstdio>
#include <cstring>
#define N 1000000
int n, m, p, cnt, ans;
int inval;
int head[N + 5];
struct Edge
{
	int v, w, nxt;
} e[N * 2 + 5];
int bel[N + 5];
int val[N + 5];
int sum[N + 5];
int col[N + 5];
int siz[N + 5];
void add_edge(int u, int v, int w)
{
	e[p].v = v;
	e[p].w = w;
	e[p].nxt = head[u];
	head[u] = p++;
	e[p].v = u;
	e[p].w = w;
	e[p].nxt = head[v];
	head[v] = p++;
}
void change(int x, int delta)
{
	sum[bel[x]] += delta;
	if(col[x] == 1)
	{
		col[x] = 0;
		val[bel[x]]--;
	}
	else
	{
		col[x] = 1;
		val[bel[x]]++;
	}
}
void dfs(int u, int id)
{
	siz[id]++;
	bel[u] = id;
	for(int i = head[u]; i != -1; i = e[i].nxt)
	{
		if(bel[e[i].v] != 0) continue;
		dfs(e[i].v, id);
	}
}
int main()
{
	memset(head, -1, sizeof(head));
	scanf("%d%d", &n, &m);
	for(int i = 0; i < m; i++)
	{
		int u, v, w;
		scanf("%d%d%d", &u, &v, &w);
		add_edge(u, v, w);
	}
	for(int i = 1; i <= n; i++)
	{
		if(bel[i] == 0)
		{
			dfs(i, ++cnt);
		}
	}
	for(int i = 0; i < m; i++)
	{
		if(e[i * 2].w == 0) continue;
		change(e[i * 2].v, 1);
		change(e[i * 2 + 1].v, 1);
	}
	for(int i = 1; i <= cnt; i++)
	{
		if(val[i] != 0) inval++;
		if(sum[i] > 0 && val[i] == 0) ans++;
	}
	int q;
	for(scanf("%d", &q); q; q--)
	{
		int op;
		scanf("%d", &op);
		if(op == 1)
		{
			int x;
			scanf("%d", &x);
			bool con = sum[bel[e[x * 2].v]] > 0 && val[bel[e[x * 2].v]] == 0;
			bool inv = val[bel[e[x * 2].v]] > 0;
			change(e[x * 2].v, e[x * 2].w == 1 ? -1 : 1);
			change(e[x * 2 + 1].v, e[x * 2 + 1].w == 1 ? -1 : 1);
			e[x * 2].w ^= 1;
			e[x * 2 + 1].w ^= 1;
			bool _con = sum[bel[e[x * 2].v]] > 0 && val[bel[e[x * 2].v]] == 0;
			bool _inv = val[bel[e[x * 2].v]] > 0;
			//printf("..%d %d\n", inv ? 1 : 0, _inv ? 1 : 0);
			if(con && !_con)
			{
				ans--;
			}
			else if(!con && _con)
			{
				ans++;
			}
			if(inv && !_inv)
			{
				inval--;
			}
			else if(!inv && _inv)
			{
				inval++;
			}
		}
		else
		{
			if(inval > 0)
			{
				printf("-1\n");
			}
			else
			{
				printf("%d\n", ans);
			}
		}
	}
	return 0;
}
