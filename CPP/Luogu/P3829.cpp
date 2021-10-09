#include <cstdio>
#include <cmath>
#include <algorithm>
struct Point
{
	double x, y;
	Point() { x = y = 0; }
	Point(double a, double b) { x = a, y = b; }
	bool operator== (const Point &p)
	{
		return p.x == x && p.y == y;
	}
};
typedef Point Vector;
const double eps = 1e-8;
int n, ptr;
double a, b, r;
int stk[400005];
Point p[400005];
bool ifEqual(double x, double y) { return fabs(x - y) <= eps; }
double getCross(Vector x, Vector y)
{
	return x.x * y.y - x.y * y.x;
}
double getDist(Point x, Point y) { return sqrt(pow(x.x - y.x, 2) + pow(x.y - y.y, 2)); }
bool Cmp(Point x, Point y)
{
	Vector _x = Vector(x.x - p[1].x, x.y - p[1].y);
	Vector _y = Vector(y.x - p[1].x, y.y - p[1].y);
	return ifEqual(getCross(_x, _y), 0) ? (getDist(x, p[1]) < getDist(y, p[1])) : (getCross(_x, _y) > 0);
}
int main()
{
	scanf("%d", &n);
	scanf("%lf%lf%lf", &a, &b, &r);
	std::swap(a, b);
	Vector v[4] = {Vector(a / 2 - r, b / 2 - r), Vector(a / 2 - r, -b / 2 + r), Vector(-a / 2 + r, b / 2 - r), Vector(-a / 2 + r, -b / 2 + r)};
	for(int i = 1; i <= n; i++)
	{
		Point t;
		scanf("%lf%lf", &t.x, &t.y);
		double theta;
		scanf("%lf", &theta);
		for(int j = 0; j < 4; j++)
		{
			double x = v[j].x * cos(theta) - v[j].y * sin(theta);
			double y = v[j].x * sin(theta) + v[j].y * cos(theta);
			int pos = (i - 1) * 4 + j + 1;
			p[pos] = Point(x + t.x, y + t.y);
			if(pos != 1)
			{
				if(p[pos].y < p[1].y || (p[pos].y == p[1].y && p[pos].x < p[1].x)) std::swap(p[pos], p[1]);
			}
		}
	}
	std::sort(p + 2, p + 1 + 4 * n, Cmp);
	int len = std::unique(p + 1, p + 1 + 4 * n) - (p + 1);
	stk[++ptr] = 1;
	for(int i = 2; i <= len; i++)
	{
		while(ptr >= 2 && getCross(Vector(p[stk[ptr]].x - p[i].x, p[stk[ptr]].y - p[i].y), Vector(p[stk[ptr]].x - p[stk[ptr - 1]].x, p[stk[ptr]].y - p[stk[ptr - 1]].y)) < 0) ptr--;
		stk[++ptr] = i;
	}
	double ans = 2 * asin(1.0) * 2 * r;
	for(int i = 1; i < ptr; i++)
	{
		ans += getDist(p[stk[i]], p[stk[i + 1]]);
	}
	ans += getDist(p[stk[ptr]], p[stk[1]]);
	printf("%.2lf", ans);
	return 0;
}
