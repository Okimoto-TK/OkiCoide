#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <vector>
#define N 700
const double epsilon = 1e-12;
int n, p, pool;
struct conn
{
	double x;
	int u, v;
};
bool cmp(conn x, conn y)
{
	return x.x < y.x;
}
int h[N + 5][N + 5];
int v[N + 5][N + 5];
conn b[N * N * 4 + 5];
int s[N * N + 5];
int siz[N * N + 5];
int max = 0;
std::vector<std::pair<int, int> > stk;
int get(int i, int j)
{
	return (i - 1) * n + j;
}
void init()
{
	for(int i = 1; i <= N * N; i++)
	{
		s[i] = i;
		siz[i] = 1;
	}
}
int find(int x)
{
	if(s[x] == x) return x;
	return find(s[x]);
}
void merge(int x, int y)
{
	int fx = find(x);
	int fy = find(y);
	if(fx == fy)
	{
		stk.push_back(std::make_pair(-1, -1));
		return;
	}
	if(siz[fx] > siz[fy])
	{
		std::swap(x, y);
		std::swap(fx, fy);
	}
	stk.push_back(std::make_pair(fx, fy));
	s[fx] = fy;
	siz[fy] += siz[fx];
	max = std::max(max, siz[fy]);
}
void divide()
{
	std::pair<int, int> t = stk.back();
	stk.pop_back();
	if(t.first == -1) return;
	s[t.first] = t.first;
	siz[t.second] -= siz[t.first];
}
void set_conn(int x, int y, int u, int v)
{
	if(x != 0 && y == 0) return;
	if(x == 0 && y == 0)
	{
		merge(u, v);
		return;
	}
	b[++pool].x = 1.0 * x / y;
	b[pool].u = u;
	b[pool].v = v;
}
bool equal(double x, double y)
{
	return std::abs(x - y) <= epsilon;
}
int main()
{
	init();
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
	{
		for(int j = 1; j <= n; j++)
		{
			scanf("%d", &h[i][j]);
		}
	}
	for(int i = 1; i <= n; i++)
	{
		for(int j = 1; j <= n; j++)
		{
			scanf("%d", &v[i][j]);
		}
	}
	// column
	for(int i = 1; i <= n; i++)
	{
		for(int j = 1; j < n; j++)
		{

			set_conn(h[i][j + 1] - h[i][j], v[i][j] - v[i][j + 1], get(i, j), get(i, j + 1));
		}
	}
	// row
	for(int i = 1; i < n; i++)
	{
		for(int j = 1; j <= n; j++)
		{
			set_conn(h[i + 1][j] - h[i][j], v[i][j] - v[i + 1][j], get(i, j), get(i + 1, j));
		}
	}
	std::sort(b + 1, b + 1 + pool, cmp);
	double mode = -1;
	int cnt = 0;
	for(int i = 1; i <= pool; i++)
	{
		if(!equal(mode, b[i].x))
		{
			for(; cnt > 0; cnt--) divide();
			mode = b[i].x;
		}
		//printf("--%d %d\n", b[i].u, b[i].v);
		merge(b[i].u, b[i].v);
		cnt++;
	}
	printf("%d", max);
	return 0;
}