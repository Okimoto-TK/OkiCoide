#include <stdio.h>
using namespace std;
void exeuc(long long a, long long b, long long & x, long long & y){
	if(b == 0){
		x = 1;
		y = 0;
		return;
	}
	exeuc(b, a % b, x, y);
	long long t = x;
	x = y;
	y = t - (a / b) * y;
}
int n;
int a[16];
int b[16];
long long crt(){
	long long M = 1;
	long long m[16];
	long long r = 0;
	for(int i = 0; i < n; i ++)
		M *= a[i];
	for(int i = 0; i < n; i ++){
		m[i] = M / a[i];
		long long x, y;
		exeuc(m[i], a[i], x, y);
		r = ((r + b[i] * m[i] * x) % M + M) % M;
	}
	return (r + M) % M;
}
int main(int argc, char const *argv[])
{
	scanf("%d", &n);
	for(int i = 0; i < n; i ++)
		scanf("%d%d", &a[i], &b[i]);
	printf("%lld", crt());
	return 0;
}