#include <math.h>
#include <stdio.h>
using namespace std;
int n;
int ans = -9999999;
int getMax(int a, int b){
	return a > b ? a : b;
}
int main(int argc, char const *argv[])
{
	scanf("%d", &n);
	for(int i = 0; i < n; i ++){
		int a;
		scanf("%d", &a);
		if(a >= 0 && double(int(sqrt(a))) == sqrt(a))
			continue;
		ans = getMax(ans, a);
	}
	printf("%d", ans);
	return 0;
}