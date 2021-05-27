#include <stdio.h>
using namespace std;
int n, m;
int a[100001];
int main(int argc, char const *argv[])
{
	scanf("%d %d", &n, &m);
	for(int i = 0; i < n; i ++)
		scanf("%d", &a[i]);
	int ptr = 0;
	int ans = 0;
	while(ptr < n){
		int sum = 0;
		for(; sum + a[ptr] <= m; ptr ++)
			sum += a[ptr];
		ans ++;
	}
	printf("%d", ans);
	return 0;
}