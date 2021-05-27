#include <stdio.h>
#include <algorithm>
using namespace std;
struct mine
{
	int m;
	int v;
	double mv;
};
bool cmp(mine a, mine b){
	return a.mv > b.mv;
}
int main(int argc, char const *argv[])
{
	int n, t;
	scanf("%d %d", &n, &t);
	mine tab[101];
	int sum = 0;
	double mny = 0;
	int ptr = 0;
	int i;
	for(i = 0; i < n; i ++){
		int a, b;
		scanf("%d %d", &a, &b);
		tab[i].m = a;
		tab[i].v = b;
		tab[i].mv = b * 1.0 / a;
	}
	sort(tab, tab + i, cmp);
	while(sum + tab[ptr].m < t){
		mny += tab[ptr].v;
		sum += tab[ptr ++].m;
		if(ptr == i){
			printf("%.2f", mny);
			return 0;
		}
	}
	mny += tab[ptr].mv * (t - sum);
	printf("%.2f", mny);
	return 0;
}