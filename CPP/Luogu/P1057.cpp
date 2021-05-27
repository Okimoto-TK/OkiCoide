#include <stdio.h>
using namespace std;
int n, m;
int f[64][64];
int main(int argc, char const *argv[])
{
	scanf("%d%d", &n, &m);
	f[0][1] = 1;
	for(int i = 1; i <= m; i ++){
		for(int j = 1; j <= n; j ++){
			f[i][j] = f[i - 1][j - 1 == 0 ? n : j - 1] + f[i - 1][j + 1 == n + 1 ? 1 : j + 1];
		}
	}
	printf("%d", f[m][1]);
	return 0;
}