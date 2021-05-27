#include <stdio.h>
using namespace std;
long long gcd(long long a, long long b){
	if(a % b == 0)
		return b;
	else
		return gcd(b, a % b);
}
int main(int argc, char const *argv[])
{
	long long a, b, c;
	scanf("%lld %lld %lld", &a, &b, &c);
	long long ab = gcd(a, b);
	long long ab_ = a * b / ab;
	long long abc = gcd(ab_, c);
	long long abc_ = ab_ * c / abc;
	printf("%lld", abc_);
	return 0;
}