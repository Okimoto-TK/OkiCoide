#include <cstdio>
#include <cmath>
#define N 10007
int n;
double x1[N];
double x2[N];
int main()
{
	scanf("%d", &n);
	for(int i = n; i >= 1; i--)
	{
		x1[i] = x1[i + 1] + double(n) / double(i);
		x2[i] = x2[i + 1] + 2 * x1[i + 1] + 1 + (double(n - i) / double(i)) * 2 * x1[i] + double(n - i) / double(i);
	}
	printf("%.2lf", (x2[1] + x1[1]) / 2);
	return 0;
}
