#include <stdio.h>
using namespace std;
struct tp
{
	int d;
	int m;
};
int m, s, t;
tp f[300007][2];
int getMax(int a, int b){
	return a > b ? a : b;
}
int main(int argc, char const *argv[])
{
	scanf("%d%d%d", &m, &s, &t);
	f[0][0].d = 0;
	f[0][1].d = 0;
	f[0][0].m = m;
	f[0][1].m = m;
	for(int i = 1; i <= t; i ++){
		if(f[i - 1][1].m >= 10){
			if(f[i - 1][0].d + 17 > f[i - 1][1].d + 60){
				f[i][0].d = f[i - 1][0].d + 17;
				f[i][0].m = f[i - 1][0].m;
			}
			else{
				f[i][0].d = f[i - 1][1].d + 60;
				f[i][0].m = f[i - 1][1].m - 10;
			}
			f[i][1].d = f[i - 1][1].d + 60;
			f[i][1].m = f[i - 1][1].m - 10;
		}
		else{
			if(f[i - 1][0].d > f[i - 1][1].d){
				f[i][0].d = f[i - 1][0].d + 17;
				f[i][0].m = f[i - 1][0].m;
			}
			else{
				f[i][0].d = f[i - 1][1].d + 17;
				f[i][0].m = f[i - 1][1].m;
			}
			f[i][1].d = f[i - 1][1].d;
			f[i][1].m = f[i - 1][1].m + 4;
		}
		if(f[i][0].d >= s){
			printf("Yes\n%d", i);
			return 0;
		}
	}
	printf("No\n%d", f[t][0].d);
	return 0;
}