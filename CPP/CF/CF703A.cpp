#include <stdio.h>
using namespace std;
int n;
int a, b;
int main(int argc, char const *argv[])
{
	scanf("%d", &n);
	for(int i = 0; i < n; i ++){
		int m, c;
		scanf("%d %d", &m, &c);
		if(m > c)
			a ++;
		else if(m != c)
			b ++;
	}
	if(a == b)
		printf("Friendship is magic!^^");
	else if(a > b)
		printf("Mishka");
	else
		printf("Chris");
	return 0;
}