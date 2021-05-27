#include <stdio.h>
using namespace std;
int n;
int a[32];
struct node
{
	int sel;
	int l;
	int r;
	int val;
};
node f[32][32];
void init(){
	for(int i = 0; i < n; i ++){
		f[i][i].val = a[i];
		f[i][i].l = i;
		f[i][i].r = i;
		f[i][i].sel = i;
	}
}
void print(int l, int r){
	printf("%d ", f[l][r].sel + 1);
	if(f[l][r].l != f[l][r].sel)
		print(f[l][r].l, f[l][r].sel - 1);
	if(f[l][r].r != f[l][r].sel)
		print(f[l][r].sel + 1, f[l][r].r);
}
int main(int argc, char const *argv[])
{
	scanf("%d", &n);
	for(int i = 0; i < n; i ++)
		scanf("%d", &a[i]);
	init();
	for(int l = 2; l <= n; l ++){
		for(int i = 0; i <= n - l; i ++){
			int j = i + l - 1;
			int max = 0;
			int mp;
			for(int rt = i; rt <= j; rt ++){
				int val;
				if(i == j)
					val = a[rt];
				else if(rt == i)
					val = 1 * f[rt + 1][j].val + a[rt];
				else if(rt == j)
					val = f[i][rt - 1].val * 1 + a[rt];
				else
					val = f[i][rt - 1].val * f[rt + 1][j].val + a[rt];
				if(val > max){
					max = val;
					mp = rt;
				}
			}
			f[i][j].sel = mp;
			f[i][j].val = max;
			f[i][j].l = i;
			f[i][j].r = j;
		}
	}
	printf("%d\n", f[0][n - 1].val);
	print(0, n - 1);
	return 0;
}