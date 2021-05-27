#include <stdio.h>
using namespace std;
int p, q;
int div;
int gcd(int a, int b){
	if(a % b == 0)
		return b;
	else
		return gcd(b, a % b);
}
int main(){
	scanf("%d %d", &p, &q);
	if(gcd(p, q) != p){
		printf("0");
		return 0;
	}
	div = q / p;
	int ans = 0;
	for(int i = div; i >= 1; i --){
		int d;
		if(div % i == 0){
			d = div / i;
			if(gcd(i, d) == 1){
				ans ++;
			}
		}
	}
	printf("%d", ans);
}