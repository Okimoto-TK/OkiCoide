#include <stdio.h>
#include <math.h>
using namespace std;
int l, m, n;
int stn[50003];
bool check(int mid){
	int p1 = 0;
	int p2 = 1;
	int del = 0;
	do{
		if(stn[p2] - stn[p1] >= mid)
			p1 = p2;
		else
			del ++;
		p2 ++;
	}while(p2 <= n + 1);
	return del <= m;
}
int main(int argc, char const *argv[])
{
	scanf("%d %d %d", &l, &n, &m);
	stn[0] = 0;
	for(int i = 1; i <= n; i ++)
		scanf("%d", &stn[i]);
	stn[n + 1] = l;
	int lt = 0;
	int r = l;
	int ans;
	while(lt <= r){
		int mid = (lt + r) / 2;
		if(check(mid)){
			ans = mid;
			lt = mid + 1;
		}
		else{
			r = mid - 1;
		}
	}
	printf("%d", ans);
	return 0;
}