#include <stdio.h>
using namespace std;
int n;
int max;
int sum;
int getMax(int a, int b){
	return a > b ? a : b;
}
int main(int argc, char const *argv[])
{
	scanf("%d", &n);
	for(int i = 0; i < n; i ++){
		int a;
		scanf("%d", &a);
		sum += a;
		max = getMax(a, max);
	}
	printf("%d", max * n - sum);
	return 0;
}