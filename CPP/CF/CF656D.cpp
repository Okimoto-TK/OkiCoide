#include <stdio.h>
using namespace std;
int a;
int main(int argc, char const *argv[])
{
	scanf("%d", &a);
	int ans = 0;
	while(a != 0){
		if(a % 8 == 1)
			ans ++;
		a /= 8;
	}
	printf("%d", ans);

