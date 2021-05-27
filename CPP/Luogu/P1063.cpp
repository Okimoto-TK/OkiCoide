#include <stdio.h>
using namespace std;
struct prl
{
	int h;
	int b;
};
int n;
int a[1024];
prl d[1024];
int f[1024][1024];
int getMax(int a, int b){
	return a > b ? a : b;
}
int main(int argc, char const *argv[])
{
	scanf("%d", &n);
	for(int i = 0; i < n; i ++){
		scanf("%d", &a[i]);
		a[i + n] = a[i];
	}
	for(int i = 0; i < n; i ++){
		d[i].h = a[i];
		d[i].b = a[i + 1];
		if(i == n - 1)
			d[i].b = a[0];
		d[i + n] = d[i];
	}
	for(int l = 0; l < 2 * n; l ++){
		for(int i = 0; i < 2 * n; i ++){
			int j = i + l;
			for(int k = i; k < j; k ++){
				f[i][j] = getMax(f[i][j], f[i][k] + f[k + 1][j] + d[i].h * d[k + 1].h * d[j].b);
			}
		}
	}
	int ans = -1;
	for(int i = 0; i < n; i ++){
		ans = getMax(ans, f[i][i + n - 1]);
	}
	printf("%d", ans);
	return 0;
}