#include <cstdio>
#include <cmath>
int n;
double x[100];
double y[100];
double r[100];
double _x1, _y1, _x2, _y2;
bool inner(double _x, double _y, int id)
{
	return r[id] * r[id] < pow(_x - x[id], 2) + pow(_y - y[id], 2);
}
int main()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
	{
		scanf("%lf", &x[i]);
	}
	for(int i = 1; i <= n; i++)
	{
		scanf("%lf", &y[i]);
	}
	for(int i = 1; i <= n; i++)
	{
		scanf("%lf", &r[i]);
	}
	scanf("%lf%lf%lf%lf", &_x1, &_y1, &_x2, &_y2);
	int ans = 0;
	for(int i = 1; i <= n; i++)
	{
		if(inner(_x1, _y1, i) ^ inner(_x2, _y2, i)) ans++;
	}
	printf("%d", ans);
	return 0;
}
