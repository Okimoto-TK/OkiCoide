#include <stdio.h>
#include <algorithm>
#include <queue>
using namespace std;
int m, n, k, l, d;
struct line
{
	int val;
	int idx;
};
line vrt[2048];
line hrz[2048];
priority_queue <int, vector<int>, greater<int> > q;
bool cmp(line a, line b){
	if(a.val == b.val)
		return a.idx < b.idx;
	return a.val > b.val;
}
int main(int argc, char const *argv[])
{
	freopen("in.in", "r", stdin);
	scanf("%d %d %d %d %d", &m, &n, &k, &l, &d);
	for(int i = 0; i < d; i ++){
		int x, y, p, q;
		scanf("%d %d %d %d", &x, &y, &p, &q);
		if(x == p){
			vrt[min(y, q)].val ++;
			vrt[min(y, q)].idx = min(y, q);
		}
		if(y == q){
			hrz[min(x, p)].val ++;
			hrz[min(x, p)].idx = min(x, p);
		}
	}
	sort(vrt, vrt + 2048, cmp);
	sort(hrz, hrz + 2048, cmp);
	for(int i = 0; i < k; i ++){
		q.push(hrz[i].idx);
	}
	while(!q.empty()){
		printf("%d ", q.top());
		q.pop();
	}
	printf("\n");
	for(int i = 0; i < l; i ++){
		q.push(vrt[i].idx);
	}
	while(!q.empty()){
		printf("%d ", q.top());
		q.pop();
	}
	return 0;
}