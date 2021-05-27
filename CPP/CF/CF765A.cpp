#include <stdio.h>
using namespace std;
int n;
int main(int argc, char const *argv[])
{
	scanf("%d", &n);
	char input[100];
	scanf("%s", input);
	for(int i = 0; i < n; i ++){
		scanf("%s", input);
	}
	if(n % 2 == 0)
		printf("home");
	else
		printf("contest");
	return 0;
}