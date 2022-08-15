#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
const double eps = 1e-8;
int n, l, w;
struct spr
{
	double a, b;
	double x, y;
} s[20005];
bool equ(double x, double y)
{
	return fabs(x - y) < eps;
}
bool cmp(spr x, spr y)
{
	if(equ(x.a, y.a)) return x.b > y.b;
	return x.a < y.a;
}
int main()
{
	while(scanf("%d", &n) != EOF)
	{
		memset(s, 0, sizeof(s));
		scanf("%d %d", &l, &w);
		for(int i = 1; i <= n; i++)
		{
			double pos, r;
			scanf("%lf %lf", &pos, &r);
			s[i].x = pos;
			s[i].y = r;
			if(double(r) <= double(w) / 2)
			{
				s[i].a = s[i].b = 0;
				continue;
			}
			s[i].a = std::max(0.0, pos - sqrt(r * r - pow(double(w) / 2, 2)));
			s[i].b = std::min(double(l), pos + sqrt(r * r - pow(double(w) / 2, 2)));
			if(s[i].a >= s[i].b) s[i].a = s[i].b = 0;
		}
		std::sort(s + 1, s + 1 + n, cmp);
		double last = 0;
		int cnt = 0;
		double max = -1;
		bool fail = false;
		for(int i = 1; i <= n && !equ(last, l); i++)
		{
			//printf("%lf %lf %lf %lf\n", s[i].a, s[i].b, s[i].x, s[i].y);
			if(s[i].a > last)
			{
				if(equ(max, -1))
				{
					fail = true;
					//continue;
					break;
				}
				last = max;
				max = -1;
				cnt++;
			}
			if(s[i].a <= last && s[i].b > last) max = std::max(max, s[i].b);
		}
		if(fail)
		{
			printf("-1\n");
			continue;
		}
		if(!equ(last, l))
		{
			if(equ(max, l))
			{
				cnt++;
				printf("%d\n", cnt);
			}
			else
			{
				printf("%d\n", -1);
			}
		}
		else
		{
			printf("%d\n", cnt);
		}
	}
	return 0;
}