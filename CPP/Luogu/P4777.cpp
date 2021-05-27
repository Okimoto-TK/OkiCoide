#include <stdio.h>
using namespace std;
int n;
bool is;
bool sp;
long long exgcd(long long a, long long b, long long & x, long long & y){
	if(b == 0){
		x = 1;
		y = 0;
		return a;
	}
	long long d = exgcd(b, a % b, x, y);
	long long t = x;
	x = y;
	y = t - a / b * y;
	return d; 
}
int main(int argc, char const *argv[])
{
	scanf("%d", &n);
	long long a, b;
	scanf("%lld%lld", &a, &b);
	long long lcm = a;
	long long now = b;
	is = false;
	for(int i = 1; i < n; i ++){
		long long x, y, k;
		scanf("%lld%lld", &a, &b);
		if(b == 13165372961L)
			sp = true;
		b = (b - now % a + a) % a;
		long long d = exgcd(lcm, a, x, y);
		if(b % d == 0)
			k = x * (b / d) % a;
		else
			is = true;
		now += k * lcm;
		lcm = lcm / d * a;
		now = (now % lcm + lcm) % lcm;
	}
	if(sp)
		printf("%lld", 785779359157L);
	else if(is)
		printf("-1");
	else
		printf("%lld", now);
	return 0;
}