#include <cstdio>
#include <bitset>
long long a, b;
int main()
{
	scanf("%lld%lld", &a, &b);
	long long c = b - a;
	std::bitset<64> _a (a);
	for(int i = 0; i < 63; i++)
	{
		if(_a[i] == 0)
		{
			if(c >= 1 << i) c -= 1 << i;
			else break;
			_a[i] = 1;
		}
	}
	printf("%d", (int)_a.count());
	return 0;
}
