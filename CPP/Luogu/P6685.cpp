#include <stdio.h>
#include <math.h>
using namespace std;
int main(){
	int n, m;
	scanf("%d %d", &n, &m);
	int ans = 0;
	for(int x = 1; true; x ++){
		if(pow(x, m) <= n)
			ans ++;
		else
			break;
	}
	printf("%d", ans);
	return 0;
}