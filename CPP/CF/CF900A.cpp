#include <stdio.h>
using namespace std;
int right;
int left;
int n;
int main(int argc, char const *argv[])
{
	scanf("%d", &n);
	for(int i = 0; i < n; i ++){
		int x, y;
		scanf("%d %d", &x, &y);
		if(x < 0)
			left ++;
		else
			right ++;
	}
	if(left <= 1 || right <= 1)
		printf("Yes");
	else
		printf("No");
	return 0;
}