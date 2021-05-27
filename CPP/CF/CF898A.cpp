#include <stdio.h>
using namespace std;
int main(int argc, char const *argv[])
{
	int n;
	scanf("%d", &n);
	if(n % 10 <= 4)
		n -= n % 10;
	else
		n += 10 - n % 10;
	printf("%d", n);
	return 0;
}