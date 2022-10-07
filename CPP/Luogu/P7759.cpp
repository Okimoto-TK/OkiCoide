#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>
#define N 100000
int n, q, p;
int head[N + 5];
struct Edge
{
	int v, nxt;
	unsigned int w;
	int d;
} e[N * 2 + 5];
int dt[N + 5];
int ans[N * 32 + 5];
void add_edge(int u, int v, unsigned int w, int d)
{
	e[++p].v = v;
	e[p].nxt = head[u];
	head[u] = p;
	e[p].w = w;
	e[p].d = d;
}
int get_id(int x, int y, int d)
{
	y = (y - d + 32);
	if(y > 32) y -= 32;
	return (x - 1) * 32 + y;
}
bool fail;
std::queue<int> qu;
void bfs(int s)
{
	qu.push(s);
	ans[s] = 0;
	while(!qu.empty() && !fail)
	{
		int u = qu.front();
		qu.pop();
		int x = (u - 1) / 32 + 1, y = (u - 1) % 32 + 1;
		for(int i = head[x]; i != -1; i = e[i].nxt)
		{
			int v = get_id(e[i].v, y, e[i].d);
			int w = (e[i].w & (1u << (32 - y))) ? 1 : 0;
			if(ans[v] != -1)
			{
				if((ans[v] ^ ans[u]) != w) fail = true;
				continue;
			}
			ans[v] = ans[u] ^ w;
			qu.push(v);
		}
	}
}
int main()
{
	memset(head, -1, sizeof(head));
	memset(ans, -1, sizeof(ans));
	scanf("%d%d", &n, &q);
	for(int i = 1; i <= q; i++)
	{
		int op, k, x;
		scanf("%d%d%d", &op, &k, &x);
		if(op == 1)
		{
			(dt[k] += x) %= 32;
		}
		else
		{
			unsigned int v;
			scanf("%u", &v);
			unsigned int t = v;
			for(int j = 1; j <= dt[k]; j++)
			{
				unsigned int b = (1u << 31) & v;
				v <<= 1;
				if(b)
				{
					v++;
				}
			}
			add_edge(k, x, v, (dt[x] - dt[k] + 32) % 32);
			v = t;
			for(int j = 1; j <= dt[x]; j++)
			{
				unsigned int b = (1u << 31) & v;
				v <<= 1;
				if(b)
				{
					v++;
				}
			}
			add_edge(x, k, v, (dt[k] - dt[x] + 32) % 32);
		}
	}
	for(int i = 1; i <= n * 32; i++)
	{
		if(ans[i] == -1)
		{
			ans[i] = 0;
			bfs(i);
		}
		if(fail)
		{
			printf("-1");
			return 0;
		}
	}
	for(int i = 1; i <= n; i++)
	{
		unsigned int val = 0;
		for(int j = 1; j <= 32; j++)
		{
			val *= 2;
			val += ans[(i - 1) * 32 + j];
		}
		printf("%u ", val);
	}
	return 0;
}