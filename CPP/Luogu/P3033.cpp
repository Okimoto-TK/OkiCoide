#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>
struct Segment
{
	int sx, sy, ex, ey;
} seg[300];
int head[300];
struct Edge
{
	int u, v, f, nxt;
	Edge() { u = v = f = nxt = -1; }
	Edge(int a, int b, int c)
	{
		u = a;
		v = b;
		f = c;
		nxt = head[a];
	}
} e[90000];
int n, s, t, ptr;
const int inf = 0x3f3f3f3f;
void AddEdge(int a, int b, int c)
{
	e[ptr] = Edge(a, b, c);
	head[a] = ptr++;
	e[ptr] = Edge(b, a, 0);
	head[b] = ptr++;
}
int dep[300];
bool Check()
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
int cur[300];
int Augmnt(int u, int f)
{
	if(u == t) return f;
	int fsum = 0;
	for(int i = cur[u]; i != -1; i = e[i].nxt)
	{
		int v = e[i].v;
		cur[u] = i;
		if(dep[v] == dep[u] + 1 && e[i].f > 0)
		{
			int _f = Augmnt(v, std::min(f, e[i].f));
			f -= _f;
			fsum += _f;
			e[i].f -= _f;
			e[i ^ 1].f += _f;
			if(f <= 0) break;
		}
	}
	return fsum;
}
int Run()
{
	int ans = 0;
	while(Check())
	{
		memcpy(cur, head, sizeof(cur));
		ans += Augmnt(s, inf);
	}
	return ans;
}
int main()
{
	memset(head, -1, sizeof(head));
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
	{
		scanf("%d%d%d%d", &seg[i].sx, &seg[i].sy, &seg[i].ex, &seg[i].ey);
	}
	s = n + 1;
	t = s + 1;
	for(int i = 1; i <= n; i++)
	{
		for(int j = 1; j <= n; j++)
		{
			if(seg[i].sx == seg[i].ex && seg[j].sx == seg[j].ex) continue;
			if(seg[i].sy == seg[i].ey && seg[j].sy == seg[j].ey) continue;
			if(seg[i].sy == seg[i].ey) continue;
			if(seg[i].sx <= std::max(seg[j].sx, seg[j].ex) && seg[i].sx >= std::min(seg[j].sx, seg[j].ex) && seg[j].sy <= std::max(seg[i].sy, seg[i].ey) && seg[j].sy >= std::min(seg[i].sy, seg[i].ey)) AddEdge(i, j, inf);
		}
		if(seg[i].sx == seg[i].ex) AddEdge(s, i, 1);
		else AddEdge(i, t, 1);
	}
	printf("%d", n - Run());
	return 0;
}
