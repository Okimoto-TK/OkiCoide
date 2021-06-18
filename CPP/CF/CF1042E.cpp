#include <cstdio>
#include <algorithm>
#define P 998244353
#define N 1005
#define N2 1000005
int n, m, ptr;
int a[N][N];
long long f[N2];
long long g[N2];
long long x[N2];
long long y[N2];
long long x2[N2];
long long y2[N2];
int c[N2];
struct Pt
{
	int x, y, v;
} _a[N2];
bool cmp(Pt a, Pt b)
{
	return a.v < b.v;
}
long long power(long long x, int k)
{
	long long r = 1;
	while(k != 0)
	{
		if((k & 1) == 1) (r *= x) %= P;
		(x *= x) %= P;
		k >>= 1;
	}
	return r;
}
int main()
{
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++)
	{
		for(int j = 1; j <= m; j++)
		{
			scanf("%d", &a[i][j]);
			int id = (i - 1) * m + j;
			_a[id].x = i;
			_a[id].y = j;
			_a[id].v = a[i][j];
		}
	}
	std::sort(_a + 1, _a + 1 + n * m, cmp);
	int sx, sy;
	scanf("%d%d", &sx, &sy);
	int last = -1;
	for(int i = 1; i <= n * m; i++)
	{
		if(_a[i].v != last)
		{
			ptr++;
			g[ptr] = g[ptr - 1];
			x[ptr] = x[ptr - 1];
			y[ptr] = y[ptr - 1];
			x2[ptr] = x2[ptr - 1];
			y2[ptr] = y2[ptr - 1];
			c[ptr] = c[ptr - 1];
		}
		f[ptr] = (g[ptr - 1] + c[ptr - 1] * power(_a[i].x, 2) + c[ptr - 1] * power(_a[i].y, 2) + x2[ptr - 1] + y2[ptr - 1] - 2 * _a[i].x * x[ptr - 1] - 2 * _a[i].y * y[ptr - 1]) % P * power(c[ptr - 1], P - 2) % P;
		if(_a[i].x == sx && _a[i].y == sy)
		{
			printf("%lld", (f[ptr] % P + P) % P);
			return 0;
		}
		(x[ptr] += _a[i].x) %= P;
		(y[ptr] += _a[i].y) %= P;
		(x2[ptr] += _a[i].x * _a[i].x) %= P;
		(y2[ptr] += _a[i].y * _a[i].y) %= P;
		c[ptr]++;
		g[ptr] += f[ptr];
		last = _a[i].v;
	}
	return 0;
}
