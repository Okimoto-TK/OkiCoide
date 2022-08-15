#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
int n, t;
double d;
struct sec
{
	double a, b;
} s[1005];
bool cmp(sec x, sec y)
{
	if(x.b == y.b) return x.a < y.a;
	return x.b < y.b;
}
int main()
{
	for(scanf("%d%lf", &n, &d); n != 0 && d != 0; scanf("%d%lf", &n, &d))
	{
		memset(s, 0, sizeof(s));
		++t;
		bool fail = false;
		for(int i = 1; i <= n; i++)
		{
			double x, y;
			scanf("%lf%lf", &x, &y);
			if(y > d)
			{
				fail = true;
				continue;
			}
			s[i].a = x - sqrt(d * d - y * y);
			s[i].b = x + sqrt(d * d - y * y);
		}
		if(fail)
		{
			printf("Case %d: %d\n", t, -1);
			continue;
		}
		std::sort(s + 1, s + 1 + n, cmp);
		double last = -1e9;
		int cnt = 0;
		for(int i = 1; i <= n; i++)
		{
			if(s[i].a <= last) continue;
			else
			{
				cnt++;
				last = s[i].b;
			}
		}
		printf("Case %d: %d\n", t, cnt);
	}
	return 0;
}