#include <stdio.h>
#include <algorithm>
#include <math.h>
using namespace std;
int main(int argc, char const *argv[])
{
	int n, q;
	scanf("%d %d", &n, &q);
	int bk[n];
	for(int i = 0; i < n; i ++){
		scanf("%d", &bk[i]);
	}
	sort(bk, bk + n);
	int pp[q][2];
	for(int i = 0; i < q; i ++){
		scanf("%d %d", &pp[i][0], &pp[i][1]);
	}
	for(int i = 0; i < q; i ++){
		int mod = pow(10, pp[i][0]);
		for(int j = 0; j < n; j ++){
			if(bk[j] % mod == pp[i][1]){
				printf("%d\n", bk[j]);
				goto end;
			}
		}
		printf("%d\n", -1);
		end:
			continue;
	}
	return 0;
}