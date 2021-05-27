// By Sublime Text 3
// P1180, by Okimoto
// No copy, pls.
#include <stdio.h>
#include <math.h>
using namespace std;
struct stn
{
	double loc;
	double prc;
};
stn gas[64];
int dis, n;
double vol, per, cst, ans;
bool flg = true;
void dfs(double ful, int loc, double sum){
	if(loc == n + 1){
		if(flg){
			ans = sum;
			flg = false;
		}
		else if(sum < ans){
			ans = sum;
		}
		return;
	}
	if((gas[loc + 1].loc - gas[loc].loc) / per > ful){
		sum += 20;
		sum += gas[loc].prc * (vol - ful);
		ful = vol;
		ful -= (gas[loc + 1].loc - gas[loc].loc) / per;
		dfs(ful, loc + 1, sum);
	}
	else if(ful < vol / 2){
		dfs(ful - (gas[loc + 1].loc - gas[loc].loc) / per, loc + 1, sum);
		sum += 20;
		sum += gas[loc].prc * (vol - ful);
		ful = vol;
		ful -= (gas[loc + 1].loc - gas[loc].loc) / per;
		dfs(ful, loc + 1, sum);
	}
	else{
		ful -= (gas[loc + 1].loc - gas[loc].loc) / per;
		dfs(ful, loc + 1, sum);
	}
}
int main(int argc, char const *argv[])
{
	scanf("%d", &dis);
	scanf("%lf %lf %lf %d", &vol, &per, &cst, &n);
	for(int i = 1; i <= n; i ++)
		scanf("%lf %lf", &gas[i].loc, &gas[i].prc);
	gas[n + 1].loc = dis;
	gas[0].loc = 0;
	dfs(vol, 0, 0);
	printf("%.1lf", ans + cst);
	return 0;
}
// 你能看到我，是我最大的心愿♥