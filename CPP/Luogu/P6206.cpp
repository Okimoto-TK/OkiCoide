#include <stdio.h>
using namespace std;
int main(int argc, char const *argv[])
{
	unsigned long long n;
	scanf("%lld", &n);
	int ans = 0;
	while(n != 1){
		if(n % 2 == 1)
			n = n * 3 + 1;
		else
			n /= 2;
		ans ++;
	}
	printf("%d", ans);
	return 0;
}