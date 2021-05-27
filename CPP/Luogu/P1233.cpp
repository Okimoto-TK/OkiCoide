#include <stdio.h>
#include <algorithm>
using namespace std;
int f[8192];
int n;
struct node
{
	int l;
	int w;
};
node a[8192];
int getMax(int a, int b){
	return a > b ? a : b;
}
bool cmp(node x, node y){
	return x.l > y.l;
}
int main()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; i ++){
		int c, b;
		scanf("%d %d", &c, &b);
		a[i].l = c;
		a[i].w = b;
	}
	sort(a + 1, a + n + 1, cmp);
	for(int i = 1; i <= n; i ++){
		int max = 0;
		for(int j = 1; j < i; j ++){
			if(a[i].w > a[j].w)
				max = getMax(max, f[j]);
		}
		f[i] = max + 1;
	}
	int ans=0;
	for(int i=1;i<=n;i++){
	    ans = getMax(ans, f[i]);
	}
	printf("%d", ans);
	return 0;
}