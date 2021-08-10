#include <cstdio>
#include <algorithm>
int n, s;
struct seg
{
	int x1, y1;
	int x2, y2;
	double k, b;
	void getKB()
	{
		if(y1 < y2)
		{
			std::swap(y1, y2);
			std::swap(x1, x2);
		}
		k = double(y1 - y2) / double(x1 - x2);
		b = double(y1) - k * x1;
	}
} a[100005];
int main()
{
	scanf("%d%d", &n, &s);
	for(int i = 1; i <= n; i++)
	{
		scanf("%d%d%d%d", &a[i].x1, &a[i].y1, &a[i].x2, &a[i].y2);
		a[i].getKB();
	}
	int x = s;
	double y = 2000000000;
	while(true)
	{
		int upr = -1;
		double mx = -2000000000;
		for(int i = 1; i <= n; i++)
		{
			if(x < std::min(a[i].x1, a[i].x2) || x > std::max(a[i].x1, a[i].x2)) continue;
			if(y <= a[i].y2) continue;
			double _y = x * a[i].k + a[i].b;
			if(_y > mx && _y <= y)
			{
				mx = _y;
				upr = i;
			}
		}
		if(upr == -1)
		{
			printf("%d", x);
			return 0;
		}
		x = a[upr].x2;
		y = a[upr].y2;
	}
	return 0;
}
