#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
int n, m;
int a[128];
int f[128][128];
const int MOD = 1000007;
int main(int argc, char const *argv[])
{
	scanf("%d %d", &n, &m);
	for(int i = 1; i <= n; i ++){
		scanf("%d", &a[i]);
	}
	f[0][0] = 1;
	for(int i = 1; i <= n; i ++){
		for(int j = 0; j <= m; j ++){
			for(int k = 0; k <= min(a[i], j); k ++){
				f[i][j] += f[i - 1][j - k];
				f[i][j] %= MOD;
			}
		}
	}
	printf("%d", f[n][m]);
	return 0;
}