#include <stdio.h>
using namespace std;
long long b, p, k;
long long ans = 1;
int main(int argc, char const *argv[])
{
	scanf("%lld %lld %lld", &b, &p, &k);
	long long op = p;
	long long ob = b;
	for(; p >= 1; p >>= 1){
		ans %= k;
		if(p & 1){
			ans *= b % k;
		}
		ans %= k;
		b = (b % k) * (b % k);
		b %= k;
	}
	ans %= k;
	printf("%lld^%lld mod %lld=%lld", ob, op, k, ans);
	return 0;
}