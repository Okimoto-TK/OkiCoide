#include <stdio.h>
using namespace std;
int ans;
int x;
int n;
int main(int argc, char const *argv[])
{
	scanf("%d", &n);
	for(int i = 0; i < n; i ++){
		scanf("%d", &x);
		ans ^= x;
	}
	printf("%d", ans);
	return 0;
}