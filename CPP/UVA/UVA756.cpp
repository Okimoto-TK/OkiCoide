#include <stdio.h>
using namespace std;
int n;
int a[16];
int b[16];
int d;
long long crt(){
	long long M = 21252;
	long long r = 0;
	for(int i = 0; i < n; i ++){
		r = ((r + b[i] * a[i]) % M + M) % M;
	}
	r = (r + M) % M;
	while(r - d <= 0)
		r += M;
	return (r - d);
}
int main(int argc, char const *argv[])
{
	long long i = 1;
	n = 3;
	a[0] = 5544;
	a[1] = -6831;
	a[2] = 1288;
	scanf("%d%d%d%d", &b[0], &b[1], &b[2], &d);
	while(b[0] != -1){
		printf("Case %lld: the next triple peak occurs in %lld days.\n", i ++, crt());
		scanf("%d%d%d%d", &b[0], &b[1], &b[2], &d);
	}
	return 0;
}