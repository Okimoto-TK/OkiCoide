#include <stdio.h>
#include <math.h>
using namespace std;
int k, n;
int t[32];
int l;
void XtoBin(int a){
	while(a != 0){
		t[l ++] = a % 2;
		a /= 2;
	}
}
long long BinToKToX(){
	long long sum = 0;
	for(int p = 0; p < l; p ++){
		sum += t[p] * pow(k, p);
	}
	return sum;
}
int main(int argc, char const *argv[])
{
	scanf("%d%d", &k, &n);
	XtoBin(n);
	printf("%lld", BinToKToX());
	return 0;
}