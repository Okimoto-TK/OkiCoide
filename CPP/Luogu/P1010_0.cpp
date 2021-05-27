#include <stdio.h>
using namespace std;
int main(){
	freopen("tab.txt", "w", stdout);
	int last = 1;
	printf("1, ");
	for(int i = 1; i <= 14; i ++){
		last *= 2;
		printf("%d, ", last);
	}
	return 0;
}