#include <cstdio>
#include <cmath>
#include <cstring>
#include <vector>
#include <algorithm>
struct Point
{
	int x, y;
	Point() { x = y = 0; }
	Point(int a, int b) { x = a, y = b; }
} p[26];
int n;
int f[1 << 24 | 1];
int g[1 << 24 | 1];
int Log2[1 << 24 | 1];
int Pow2[24];
int Cnt[1 << 24 | 1];
int dist[30][30];
std::vector<int> v[25];
inline int Count(int x)
{
	if(Cnt[x] != 0) return Cnt[x];
	int res = 0;
	for(; x; x &= (x - 1)) res++;
	Cnt[x] = res;
	return res;
}
inline int getDist(Point a, Point b) { return pow(a.x - b.x, 2) + pow(a.y - b.y, 2); }
int main() {
	scanf("%d%d", &p[0].x, &p[0].y);
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
	{
		scanf("%d%d", &p[i].x, &p[i].y);
	}
	for(int i = 0; i < 1 << n; i++)
	{
		v[Count(i)].push_back(i);
	}
	for(int i = 0, x = 1; i <= n; i++, x <<= 1) Pow2[i] = x;
	for(int i = 0; i <= n; i++)
	{
		for(int j = 0; j <= n; j++) dist[i][j] = getDist(p[i], p[j]);
	}
	Log2[1] = 0;
	for(int i = 1; i < n; i++)
	{
		for(int j = Pow2[i]; j < Pow2[i + 1]; j++) Log2[j] = i;
	}
	memset(f, 0x3f, sizeof(f));
	f[0] = 0;
	for(int i = 1; i <= n; i++)
	{
		int len = v[i].size();
		for(int _i = 0, bin = v[i][_i]; _i < len; _i++, bin = v[i][_i])
		{
			for(int _x = bin; _x != 0; _x -= (-_x & _x))
			{
				int x = _x & (-_x);
				int tmp, _bin;
				if(x & bin)
				{
					_bin = bin ^ x;
					tmp = f[_bin] + 2 * dist[0][Log2[x] + 1];
					if(tmp < f[bin])
					{
						f[bin] = tmp;
						g[bin] = _bin;
					}
				}
				else continue;
				for(int _y = _x - (_x & -_x); _y != 0; _y -= (-_y & _y))
				{
					int y = _y & (-_y);
					if(y & bin)
					{
						int _bin = bin ^ x ^ y;
						tmp = f[_bin] + dist[0][Log2[x] + 1] + dist[0][Log2[y] + 1] + dist[Log2[x] + 1][Log2[y] + 1];
						if(tmp < f[bin])
						{
							f[bin] = tmp;
							g[bin] = _bin;
						}
					}
				}
				break;
			}
		}
	}
	printf("%d\n", f[Pow2[n] - 1]);
	for(int i = Pow2[n] - 1; i != 0; i = g[i])
	{
		printf("0 ");
		int j = g[i];
		int x = (i ^ j);
		x = Log2[x] + 1;
		printf("%d ", x);
		if(Count(i ^ j) == 2)
		{
			int y = (i ^ j) ^ (Pow2[x - 1]);
			y = Log2[y] + 1;
			printf("%d ", y);
		}
	}
	printf("0");
	return 0;
}
