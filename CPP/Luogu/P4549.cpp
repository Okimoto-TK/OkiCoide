#include <cstdio>
#include <cmath>
int n, last;
int gcd(int x, int y)
{
	if(y == 0) return x;
	return gcd(y, x % y);
}
int main()
{
	scanf("%d", &n);
	scanf("%d", &last);
	last = abs(last);
	for(int i = 2; i <= n; i++)
	{
		int a;
		scanf("%d", &a);
		a = abs(a);
		last = gcd(last, a);
	}
	printf("%d", last);
	return 0;
}
