#include <cstdio>
#define N 100005
int n;
double x1[N];
double x2[N];
int main()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
	{
		double pos;
		scanf("%lf", &pos);
		(x1[i] = x1[i - 1] + 1) *= pos;
		x2[i] = x2[i - 1] + pos * (2 * x1[i - 1] + 1);
	}
	printf("%.7lf", x2[n]);
	return 0;
}
