#include <stdio.h>
#include <algorithm>
using namespace std;
int n, m;
struct edge
{
	int a;
	int b;
	int wt;
};
edge e[200001];
int s[5001];
bool cmp(edge a, edge b){
	return a.wt < b.wt;
}
void init(){
	for(int i = 0; i < 5001; i ++)
		s[i] = i;
}
int find(int x){
	if(s[x] == x)
		return x;
	else{
		int r = find(s[x]);
		s[x] = r;
		return r;
	}
}
int main(int argc, char const *argv[])
{
	init();
	scanf("%d %d", &n, &m);
	for(int i = 0; i < m; i ++)
		scanf("%d %d %d", &e[i].a, &e[i].b, &e[i].wt);
	sort(e, e + m, cmp);
	int sum = 0;
	for(int i = 0; i < m; i ++){
		if(find(e[i].a) == find(e[i].b)){
			continue;
		}
		s[find(e[i].a)] = find(e[i].b);
		sum += e[i].wt;
	}
	printf("%d", sum);
	return 0;
}