#include <stdio.h>
using namespace std;
int bucket[1002][1002];
int n, m;
int main(int argc, char const *argv[])
{
	scanf("%d %d", &n, &m);
	for(int i = 0; i < m; i ++){
		int x1, y1, x2, y2;
		scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
		for(int x = x1; x <= x2; x ++)
			for(int y = y1; y <= y2; y ++)
				bucket[x][y] ++;
	}
	for(int i = 1; i <= n; i ++){
		for(int j = 1; j <= n; j ++)
			printf("%d ", bucket[i][j]);
		printf("\n");
	}
	return 0;
}