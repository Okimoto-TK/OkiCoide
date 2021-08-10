#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
int get(char c)
{
	if(c <= 'Z' && c >= 'A') return c - 'A' + 1;
	return c - 'a' + 27;
}
int head[60];
struct E
{
	int u, v, f, nxt;
	E(){ u = v = f = nxt = -1; }
	E(int a, int b, int c)
	{
		u = a;
		v = b;
		f = c;
		nxt = head[a];
	}
} edge[1500];
int ptr;
void add_edge(int a, int b, int c)
{
	edge[ptr] = E(a, b, c);
	head[a] = ptr++;
	edge[ptr] = E(b, a, c);
	head[b] = ptr++;
}
int d[60];
int tr[60];
int bfs()
{
	int ans = 0;
	while(true)
	{
		memset(d, 0, sizeof(d));
		d[1] = 1024;
		std::queue<int> q;
		q.push(1);
		while(!q.empty())
		{
			int u = q.front();
			q.pop();
			for(int i = head[u]; i != -1; i = edge[i].nxt)
			{
				int v = edge[i].v;
				if(d[v] == 0 && edge[i].f > 0)
				{
					d[v] = std::min(d[u], edge[i].f);
					q.push(v);
					tr[v] = i;
				}
			}
			if(d[26] != 0) break;
		}
		if(d[26] == 0) break;
		for(int i = 26; i != 1; i = edge[tr[i]].u)
		{
			edge[tr[i]].f -= d[26];
			edge[tr[i] ^ 1].f += d[26];
		}
		ans += d[26];
	}
	return ans;
}
int n;
int main()
{	
	for(int i = 1; i <= 55; i++) head[i] = -1;
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
	{
		char a[2], b[2];
		int f;
		scanf("%s%s%d", a, b, &f);
		add_edge(get(a[0]), get(b[0]), f);
	}
	printf("%d", bfs());
	return 0;
}
