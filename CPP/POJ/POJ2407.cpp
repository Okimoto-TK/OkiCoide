#include <cstdio>
#include <cmath>
int main()
{
	int n;
	for(scanf("%d", &n); n != 0; scanf("%d", &n))
	{
		int gate = sqrt(double(n));
		int ans = 1;
		int x = n;
		for(int i = 2; i <= gate; i++)
		{
			if(x % i == 0)
			{
				int pow = 1;
				while(x % i == 0)
				{
					x /= i;
					pow *= i;
				}
				pow /= i;
				ans *= (i - 1) * pow;
			}
		}
		if(x != 1) ans *= x - 1;
		printf("%d\n", ans);
	}
	return 0;
}