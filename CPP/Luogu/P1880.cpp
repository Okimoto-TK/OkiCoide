#include <stdio.h>
using namespace std;
int n;
int a[512];
int fax[512][512];
int fin[512][512];
int sum[512];
int max(int a, int b){
	return a > b ? a : b;
}
int min(int a, int b){
	return a < b ? a : b;
}
void init(){
	for(int i = 0; i < 256; i ++){
		fax[i][i] = 0;
		fin[i][i] = 0;
		for(int j = 0; j < 256; j ++){
			if(j == i)
				continue;
			fin[i][j] = 1000000000;
		}
	}
}
int main(int argc, char const *argv[])
{
	init();
	scanf("%d", &n);
	for(int i = 0; i < n; i ++){
		scanf("%d", &a[i]);
		a[n + i] = a[i];
	}
	sum[0] = 0;
	for(int i = 1; i <= 2 * n; i ++){
		sum[i] = sum[i - 1] + a[i - 1];
	}
	for(int l = 1; l < 2 * n; l ++){
		for(int i = 0; i < n * 2; i ++){
			int j = i + l;
			for(int k = i; k < j; k ++){
				fax[i][j] = max(fax[i][j], fax[i][k] + fax[k + 1][j] + sum[j + 1] - sum[i]);
			}
			for(int k = i; k < j; k ++){
				fin[i][j] = min(fin[i][j], fin[i][k] + fin[k + 1][j] + sum[j + 1] - sum[i]);
			}
		}
	}
	int mx = 0;
	int mn = 1000000000;
	for(int i = 0; i <= n; i ++){
		if(fax[i][i + n - 1] > mx)
			mx = fax[i][i + n - 1];
		if(fin[i][i + n - 1] < mn){
			mn = fin[i][i + n - 1];
		}
	}
	printf("%d\n%d", mn, mx);
	return 0;
}