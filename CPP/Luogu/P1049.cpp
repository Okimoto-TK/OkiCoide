#include <stdio.h>
using namespace std;
long long v;
long long n;
long long w[64];
long long f[20007];
long long getMax(long long a, long long b){
	return a > b ? a : b;
}
int main(int argc, char const *argv[])
{
	scanf("%lld", &v);
	scanf("%lld", &n);
	for(long long i = 0; i < n; i ++)
		scanf("%lld", &w[i]);
	for(long long i = 0; i < n; i ++){
		for(long long l = v; l >= 1; l --){
			f[l] = getMax(f[l], l >= w[i] ? f[l - w[i]] + w[i] : 0);
		}
	}
	printf("%lld", v - f[v]);
	return 0;
}