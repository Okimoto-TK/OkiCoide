#include <stdio.h>
#include <stack>
#pragma GCC optimize(2)
using namespace std;
int ans;
void dfs(int n){
	ans ++;
	for(int i = 1; i <= n / 2; i ++){
		dfs(i);
	}
}
int main(int argc, char const *argv[])
{
	for(int i = 1; i <= 1000; i ++){
		freopen("tab.txt", "a", stdout);
		ans = 0;
		dfs(i);
		printf("%d, ", ans);
		freopen("CON", "w", stdout);
		printf("#%d Has Done!\n", i);
	}
	return 0;
}