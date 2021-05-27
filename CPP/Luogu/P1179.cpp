#include <stdio.h>
#pragma GCC optimize(2)
using namespace std;
int cntTwo(int x){
	if(x == 0)
		return 0;
	int m = x % 10;
	x /= 10;
	int p;
	if(m == 2)
		p = 1;
	else
		p = 0;
	return cntTwo(x) + p;
}
int main(int argc, char const *argv[])
{
	long long ans = 0;
	int l, r;
	scanf("%d %d", &l, &r);
	for(int i = l; i <= r; i ++)
		ans += cntTwo(i);
	printf("%lld", ans);
	return 0;
}