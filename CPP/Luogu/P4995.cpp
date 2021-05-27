#include <stdio.h>
#include <algorithm>
using namespace std;
int main(int argc, char const *argv[])
{
	int n;
	scanf("%d", &n);
	int stn[n + 1];
	for(int i = 0; i < n; i ++)
		scanf("%d", &stn[i]);
	stn[n] = 0;
	sort(stn, stn + n + 1);
	int l = 0;
	int r = n;
	long long ans = 0;
	while(l < r){
		ans += (stn[r] - stn[l]) * (stn[r] - stn[l]);
		l ++;
		if(l >= r)
			 break;
		ans += (stn[l] - stn[r]) * (stn[l] - stn[r]);
		r --;
	}
	printf("%lld", ans);
	return 0;
}