#include <stdio.h>
using namespace std;
struct blk
{
	int a;
	int b;
	int g;
	int k;
};
blk bk[10001];
int n;
int x;
int y;
int main(int argc, char const *argv[])
{
	scanf("%d", &n);
	for(int i = 0; i < n; i ++)
		scanf("%d %d %d %d", &bk[i].a, &bk[i].b, &bk[i].g, &bk[i].k);
	scanf("%d %d", &x, &y);
	for(int i = n - 1; i >= 0; i --){
		if(bk[i].a <= x && bk[i].b <= y && bk[i].a + bk[i].g >= x && bk[i].b + bk[i].k >= y){
			printf("%d", i + 1);
			return 0;
		}
	}
	printf("-1");
	return 0;
}