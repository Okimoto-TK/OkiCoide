#include <stdio.h>
using namespace std;
long long gcd(long long a, long long b){
	if(b == 0)
		return a;
	else
		return gcd(b, a % b);
}
long long n, m, x;
long long fastPow(long long k){
	long long r = 1;
	long long a = 10;
	while(k){
		if(k % 2 == 1)
			r = r * a % n;
		a = a * a % n;
		k /= 2;
	}
	return r;
}
long long k;
int main(int argc, char const *argv[])
{
	scanf("%lld%lld%lld%lld", &n, &m, &k, &x);
	long long a = fastPow(k) % n * m % n;
	a += x;
	a %= n;
	printf("%lld", a);
	return 0;
}