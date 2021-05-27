#include <stdio.h>
using namespace std;
int n;
long long a[128][128];
long long s[128][128];
int main(int argc, char const *argv[])
{
	scanf("%lld", &n);
	for(int i = 1; i <= n; i ++){
		for(int j = 1; j <= n; j ++){
			scanf("%lld", &a[i][j]);
			s[i][j] = a[i][j] + s[i - 1][j] + s[i][j - 1] - s[i - 1][j - 1];
		}
	}
	long long ans = -1000000;
	for(int x1 = 1; x1 <= n; x1 ++){
		for(int y1 = 1; y1 <= n; y1 ++){
			for(int x2 = x1; x2 <= n; x2 ++){
				for(int y2 = y1; y2 <= n; y2 ++){
					int temp = s[x2][y2] - s[x2][y1 - 1] - s[x1 - 1][y2] + s[x1 - 1][y1 - 1];
					ans = ans > temp ? ans : temp;
				}
			}
		}
	}
	printf("%lld", ans);
	return 0;
}