#include <cstdio>
#include <cmath>
#include <algorithm>
struct Point
{
	int x, y;
} p[705];
const double eps = 1e-6;
int n;
bool ifZero(double x)
{
	return fabs(x) <= eps;
}
int main()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
	{
		scanf("%d%d", &p[i].x, &p[i].y);
	}
	int ans = 0;
	for(int i = 1; i <= n; i++)
	{
		for(int j = i + 1; j <= n; j++)
		{
			double k = double(p[j].y - p[i].y) / double(p[j].x - p[i].x);
			double b = p[i].y - k * p[i].x;
			int cnt = 0;
			for(int x = 1; x <= n; x++)
			{
				if(ifZero(k * p[x].x + b - p[x].y)) cnt++;
			}
			ans = std::max(ans, cnt);
		}
	}
	printf("%d", ans);
	return 0;
}
