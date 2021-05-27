#include <stdio.h>
#include <algorithm>
using namespace std;
int rr[1000010];
int cr[1000010];
int n, k;
int main(int argc, char const *argv[])
{
	scanf("%d %d", &n, &k);
	for(int i = 0; i < k; i ++){
		scanf("%lld %lld", &rr[i], &cr[i]);
	}
	sort(rr, rr + k);
	sort(cr, cr + k);
	int lc = -1;
	int lr = -1;
	unsigned long long cs = 0;
	unsigned long long rs = 0;
	for(int i = 0; i < k; i ++){
		if(rr[i] != lr){
			lr = rr[i];
			rs ++;
		}
		if(cr[i] != lc){
			lc = cr[i];
			cs ++;
		}
	}
	unsigned long long ans = cs * n + rs * n - rs * cs;
	printf("%lld", ans);
	return 0;
}