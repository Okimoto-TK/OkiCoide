#include <stdio.h>
#include <algorithm>
using namespace std;
struct edge
{
	int x;
	int y;
	int l;
} e[10007];
int n, m, k;
int s[1007];
int ans;
int cnt;
bool cmp(edge a, edge b){
	return a.l < b.l;
}
void init(){
	for(int i = 0; i < 1007; i ++)
		s[i] = i;
}
int _find(int a){
	if(s[a] == a)
		return a;
	else{
		s[a] = _find(s[a]);
		return s[a];
	}
}
int main(int argc, char const *argv[])
{
	init();
	scanf("%d%d%d", &n, &m, &k);
	if(n < k){
		printf("No Answer");
		return 0;
	}
	cnt = n - k;
	for(int i = 0; i < m; i ++)
		scanf("%d%d%d", &e[i].x, &e[i].y, &e[i].l);
	sort(e, e + m, cmp);
	int ced = 0;
	for(int i = 0; i < m && ced < cnt; i ++){
		if(_find(e[i].x) != _find(e[i].y)){
			s[_find(e[i].x)] = _find(e[i].y);
			ced ++;
			ans += e[i].l;
		}
	}
	if(ced < cnt){
		printf("No Answer");
		return 0;
	}
	printf("%d", ans);
	return 0;
}