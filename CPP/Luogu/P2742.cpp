#include <cstdio>
#include <cmath>
#include <algorithm>
const double _inf = -(1e6 + 7);
const double eps = 1e-8;
int n;
struct Point
{
	double x, y;
	Point() { x = y = _inf; }
	Point(double a, double b) { x = a, y = b; }
} a[100005];
typedef Point Vector;
double Cross(Vector a, Vector b)
{
	return a.x * b.y - a.y * b.x;
}
double Equal(double a, double b)
{
	return fabs(a - b) <= eps;
}
bool cmp(Point x, Point y)
{
	double cr = Cross(Vector(x.x - a[1].x, x.y - a[1].y), Vector(y.x - a[1].x, y.y - a[1].y));
	if(Equal(cr, 0)) return sqrt(pow(x.x - a[1].x, 2) + pow(x.y - a[1].y, 2)) < sqrt(pow(y.x - a[1].x, 2) + pow(y.y - a[1].y, 2));
	else return cr > 0;
}
int stk[100005];
int ptrTop;
int main()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
	{
		scanf("%lf%lf", &a[i].x, &a[i].y);
	}
	for(int i = 2; i <= n; i++)
	{
		if(a[i].y < a[1].y || (a[i].y == a[1].y && a[i].x < a[1].x)) std::swap(a[i], a[1]);
	}
	std::sort(a + 2, a + 1 + n, cmp);
	for(int i = 1; i <= n; i++)
	{
		if(ptrTop <= 1) stk[++ptrTop] = i;
		else
		{
			while(ptrTop >= 2 && Cross(Vector(a[stk[ptrTop]].x - a[i].x, a[stk[ptrTop]].y - a[i].y), Vector(a[stk[ptrTop]].x - a[stk[ptrTop - 1]].x, a[stk[ptrTop]].y - a[stk[ptrTop - 1]].y)) < 0) ptrTop--;
			stk[++ptrTop] = i;
		}
	}
	double ans = 0;
	for(int i = 2; i <= ptrTop; i++)
	{
		ans += sqrt(pow(a[stk[i]].x - a[stk[i - 1]].x, 2) + pow(a[stk[i]].y - a[stk[i - 1]].y, 2));
	}
	ans += sqrt(pow(a[stk[ptrTop]].x - a[1].x, 2) + pow(a[stk[ptrTop]].y - a[1].y, 2));
	printf("%.2lf", ans);
	return 0;
}
