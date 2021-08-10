#include <cstdio>
#include <cmath>
#include <algorithm>
#define P 998244353
int n;
unsigned long long v;
struct node
{
	long long x, y;
} a[1000005];
bool cmp1(node a, node b)
{
	if(a.x == b.x) return a.y > b.y;
	return a.x < b.x;
}
bool cmp2(node a, node b)
{
	if(a.x == b.x) return a.y < b.y;
	return a.x < b.x;
}
bool cmp3(node a, node b)
{
	if(a.y == b.y) return a.x < b.x;
	return a.y < b.y;
}
bool cmp4(node a, node b)
{
	if(a.y == b.y) return a.x > b.x;
	return a.y < b.y;
}
long long pow(long long a){ return (a * a); }
bool check(int i)
{
	if((unsigned long long)pow(a[i].x - a[i - 1].x) + (unsigned long long)pow(a[i].y - a[i - 1].y) + (unsigned long long)pow(a[i - 1].x - a[i - 2].x) + (unsigned long long)pow(a[i - 1].y - a[i - 2].y) == (unsigned long long)pow(a[i].x - a[i - 2].x) + (unsigned long long)pow(a[i].y - a[i - 2].y)) return true;
	return false;
}
bool valid()
{
	for(int i = 2; i <= n; i++)
	{
		if(!check(i)) return false;
	}
	return true;
}
long long power(long long x, int k)
{
	long long r = 1;
	while(k != 0)
	{
		if(k & 1) (r *= x) %= P;
		(x *= x) %= P;
		k >>= 1;
	}
	return r;
}
int main()
{
	scanf("%d%lld", &n, &v);
	for(int i = 0; i <= n; i++)
	{
		scanf("%lld%lld", &a[i].x, &a[i].y);
	}
	std::sort(a, a + 1 + n, cmp1);
	if(!valid())
	{
		std::sort(a, a + 1 + n, cmp2);
		if(!valid())
		{
			std::sort(a, a + 1 + n, cmp3);
			if(!valid())
			{
				std::sort(a, a + 1 + n, cmp4);
			}
		}
	}
	long long sum = 0;
	for(int i = 1; i <= n; i++)
	{
		sum += ((long long)pow(a[i].x - a[i - 1].x) % P + (long long)pow(a[i].y - a[i - 1].y) % P) % P;
		sum %= P;
	}
	printf("%lld", (power(v * v % P, P - 2) * (sum % P) % P + P) % P);
	return 0;
}

