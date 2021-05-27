#include <stdio.h>
using namespace std;
int n;
int f[1024][1024];
int getMax(int a, int b){
	return a > b ? a : b;
}
int main(int argc, char const *argv[])
{
	scanf("%d", &n);
	for(int i = 0; i < n; i ++)
		scanf("%d", &f[i][i]);
	for(int l = 1; l < n; l ++){
		for(int i = 0; i < n; i ++){
			int j = i + l;
			for(int k = i; k < j; k ++){
				if(f[i][k] == f[k + 1][j] && f[i][k] != 0 && f[k + 1][j] != 0)
					f[i][j] = getMax(f[i][j], f[i][k] + 1);
			}
		}
	}
	int ans = -1;
	for(int i = 0; i < n; i ++){
		for(int j = i; j < n; j ++)
			ans = getMax(ans, f[i][j]);
	}
	printf("%d", ans);
	return 0;
}