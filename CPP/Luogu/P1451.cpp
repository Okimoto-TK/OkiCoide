#include <stdio.h>
using namespace std;
int n, m;
int tar[128][128];
void dfs(int x, int y){
	if(tar[x][y] == 0)
		return;
	tar[x][y] = 0;
	if(x != 0){
		dfs(x - 1, y);
	}
	if(x != n - 1){
		dfs(x + 1, y);
	}
	if(y != 0){
		dfs(x, y - 1);
	}
	if(y != m - 1){
		dfs(x, y + 1);
	}
}
int main(int argc, char const *argv[])
{
	int ans = 0;
	scanf("%d %d\n", &n, &m);
	for(int i = 0; i < n; i ++)
		for(int j = 0; j < m; j ++)
			scanf("%1d", &tar[i][j]);
	for(int i = 0; i < n; i ++){
		for(int j = 0; j < m; j ++){
			if(tar[i][j] != 0){
				ans ++;
				dfs(i, j);
			}
		}
	}
	printf("%d", ans);
	return 0;
}