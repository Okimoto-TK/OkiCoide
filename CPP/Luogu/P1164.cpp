#include <stdio.h>
using namespace std;
int prc[105];
int ans, n, m;
void dfs(int sum, int last){
	if(sum == m){
		ans ++;
		return;
	}
	if(sum > m)
		return;
	for(int i = last; i <= n; i ++){
		dfs(sum + prc[i], i + 1);
	}
}
int main(int argc, char const *argv[])
{
	scanf("%d %d", &n, &m);
	for(int i = 1; i <= n; i ++){
		scanf("%d", &prc[i]);
	}
	dfs(0, 1);
	printf("%d", ans);
	return 0;
}