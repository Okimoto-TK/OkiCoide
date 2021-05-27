#include <stdio.h>
using namespace std;
long long m, n;
const long long MOD = 100003;
long long fastPow(long long a, long long k){
	long long r = 1;
	while(k){
		if(k & 1)
			r = (a * r) % MOD;
		a = (a * a) % MOD;
		k /= 2;
	}
	return r % MOD;
}
int main(int argc, char const *argv[])
{
	scanf("%lld%lld", &m, &n);
	long long all = fastPow(m, n) + MOD;
	long long nJB = fastPow(m - 1, n - 1) * (m % MOD) % MOD;
	long long jB = all - nJB;
	printf("%lld", jB % MOD); 
	return 0;
}