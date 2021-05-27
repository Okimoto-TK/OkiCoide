#include <stdio.h>
using namespace std;
int n, m;
int a[10007];
char ans[256000];
int ptr = 0;
int find(int x){
	if(a[x] != x)
		return find(a[x]);
	else
		return x;
}
void init(){
	for(int i = 0; i < 10007; i ++)
		a[i] = i;
}
int main(int argc, char const *argv[])
{
	init();
	scanf("%d %d", &n, &m);
	for(int i = 0; i < m; i ++){
		int z, x, y;
		scanf("%d %d %d", &z, &x, &y);
		a[x] = find(x);
		a[y] = find(y);
		if(z == 1){
			a[find(x)] = find(y);
		}
		else{
			ans[ptr ++] = find(x) == find(y) ? 'Y' : 'N';
		}
	}
	for(int i = 0; i < ptr; i ++)
		printf("%c\n", ans[i]);
	return 0;
}