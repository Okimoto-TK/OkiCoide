#include <stdio.h>
#include <algorithm>
#include <math.h>
using namespace std;
struct nd
{
	int begin;
	int end; 
};
bool tick[1000002];
nd seg[1000002];
bool cmp(nd x, nd y){
	if(x.end == y.end)
		return x.begin > y.begin;
	else
		return x.end < y.end;
}
int main(int argc, char const *argv[])
{
	int n;
	int ans = 0;
	scanf("%d", &n);
	for(int i = 0; i < n; i ++)
		scanf("%d %d", &seg[i].begin, &seg[i].end);

	sort(seg, seg + n, cmp);
	for(int i = 0; i < n; i ++){
		for(int j = seg[i].begin; j < seg[i].end; j ++)
			if(tick[j])
				goto end;
		for(int j = seg[i].begin; j < seg[i].end; j ++)
			tick[j] = true;
		ans ++;
		end:
			continue;
	}
	printf("%d", ans);
	return 0;
}