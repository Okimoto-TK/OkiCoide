#include <stdio.h>
using namespace std;
int n, t;
int ans;
int main(int argc, char const *argv[])
{
	scanf("%d %d", &n, &t);
	for(int i = 0; i < n; i ++){
		int a;
		scanf("%d", &a);
		if(t > 0){
			t -= 86400 - a;
			ans ++;
		}
	}
	printf("%d", ans);
	return 0;
}