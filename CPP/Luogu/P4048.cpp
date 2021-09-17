#include <cstdio>
#include <cstring>
#include <cmath>
#include <queue>
#include <algorithm>
#define int long long
struct Lich
{
	int x, y, r, t;
} lc[205];
struct Elf
{
	int x, y;
} el[205];
struct Trees
{
	int x, y, r;
} tr[205];
int head[2005];
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
} e[4000005];
int n, m, k, ptr, s, t;
bool val[205][205];
bool Cosine(double a, double b, double c)
{
	return a + b > c;
}
double GetDis(int x1, int x2, int y1, int y2)
{
	return pow(x1 - x2, 2) + pow(y1 - y2, 2);
}
bool IsValid(int lich, int elf)
{
	if(pow(lc[lich].x - el[elf].x, 2) + pow(lc[lich].y - el[elf].y, 2) > lc[lich].r * lc[lich].r) return false;
	for(int i = 1; i <= k; i++)
	{
		double R;
		if(lc[lich].x == el[elf].x)
		{
			R = pow(tr[i].x - lc[lich].x, 2);
		}
		else if(lc[lich].y == el[elf].y)
		{
			R = pow(tr[i].y - lc[lich].y, 2);
		}
		else
		{
			double k = double(lc[lich].y - el[elf].y) / double(lc[lich].x - el[elf].x);
			double b = lc[lich].y - k * lc[lich].x;
			R = pow(k * tr[i].x - tr[i].y + b, 2) / (k * k + 1);
		}
		if(R >= tr[i].r * tr[i].r) continue;
		double o = GetDis(lc[lich].x, el[elf].x, lc[lich].y, el[elf].y);
		double p = GetDis(lc[lich].x, tr[i].x, lc[lich].y, tr[i].y);
		double q = GetDis(el[elf].x, tr[i].x, el[elf].y, tr[i].y);
		if(Cosine(o, p, q) && Cosine(o, q, p)) return false;
	}
	return true;
}
void AddEdge(int a, int b, int c)
{
	e[ptr] = Edge(a, b, c);
	head[a] = ptr++;
	e[ptr] = Edge(b, a, 0);
	head[b] = ptr++;
}
int dep[2005];
bool Bfs()
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
int cur[2005];
int Dfs(int u, int f)
{
	if(u == t) return f;
	int fsum = 0;
	for(int i = cur[u]; i != -1; i = e[i].nxt)
	{
		cur[u] = i;
		int v = e[i].v;
		if(dep[v] == dep[u] + 1 && e[i].f > 0)
		{
			int _f = Dfs(v, std::min(f, e[i].f));
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
	while(Bfs())
	{
		memcpy(cur, head, sizeof(cur));
		ans += Dfs(s, 0x3f3f3f3f);
	}
	return ans;
}
bool Check(int x)
{
	ptr = 0;
	memset(head, -1, sizeof(head));
	for(int i = 1; i <= n; i++)
	{
		AddEdge(s, i, x / lc[i].t + 1);
		for(int j = 1; j <= m; j++)
		{
			if(val[i][j]) AddEdge(i, j + n, 1);
		}
	}
	for(int i = 1; i <= m; i++)
	{
		AddEdge(i + n, t, 1);
	}
	return Run() >= m;
}
signed main()
{
	scanf("%lld%lld%lld", &n, &m, &k);
	s = n + m + 1;
	t = s + 1;
	for(int i = 1; i <= n; i++)
	{
		scanf("%lld%lld%lld%lld", &lc[i].x, &lc[i].y, &lc[i].r, &lc[i].t);
	}
	for(int i = 1; i <= m; i++)
	{
		scanf("%lld%lld", &el[i].x, &el[i].y);
	}
	for(int i = 1; i <= k; i++)
	{
		scanf("%lld%lld%lld", &tr[i].x, &tr[i].y, &tr[i].r);
	}
	for(int i = 1; i <= n; i++)
	{
		for(int j = 1; j <= m; j++) 
		{
			val[i][j] = IsValid(i, j);
		}
	}
	int l = 0, r = 4000000;
	bool suc = false;
	while(l < r)
	{
		int mid = (l + r) >> 1;
		if(Check(mid))
		{
			r = mid;
			suc = true;
		}
		else l = mid + 1;
	}
	if(!suc) printf("-1");
	else printf("%lld", l);
	return 0;
}
