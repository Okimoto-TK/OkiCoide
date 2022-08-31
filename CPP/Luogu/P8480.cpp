#include <cstdio>
#include <cmath>
#include <algorithm>
int n, m;
long long min, max;
int main()
{
	min = 0x3f3f3f3f3f;
	max = -0x3f3f3f3f3f;
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++)
	{
		long long a;
		scanf("%lld", &a);
		min = std::min(min, a);
		max = std::max(max, a);
	}
	if(std::abs(min) <= 1 && std::abs(max) <= 1)
	{
		if(max >= -min)
		{
			max += 2;
			m--;
		}
		else
		{
			min -= 2;
			m--;
		}
	}
	//printf("%lld %lld\n", max, min);
	if(std::abs(max) >= std::abs(min))
	{
		max *= pow(2, m);
	}
	else
	{
		min *= pow(2, m);
	}
	printf("%lld", max - min);
	return 0;
}