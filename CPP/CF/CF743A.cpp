#include <stdio.h>
using namespace std;
int n, a, b;
int l[1000001];
int main(int argc, char const *argv[])
{
	scanf("%d %d %d", &n, &a, &b);
	for(int i = 0; i < n; i ++){
		scanf("%1d", &l[i]);
	}
	if(l[a - 1] != l[b - 1])
		printf("1");
	else
		printf("0");
	return 0;
}