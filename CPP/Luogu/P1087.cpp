#include <stdio.h>
#include <math.h>
using namespace std;
int n;
int len;
char str[2048];
char tree[2048];
void dfs(int l, int r, int p){
	bool b = false;
	bool i = false;
	for(int j = l; j <= r; j ++){
		if(str[j] == '0')
			b = true;
		if(str[j] == '1')
			i = true;
	}
	tree[p] = i && b ? 'F' : (i ? 'I' : 'B');
	if(l != r){
		dfs(l, (l + r) / 2, 2 * p);
		dfs((l + r) / 2 + 1, r, 2 * p + 1);
	}
}
void print(int p){
	if(tree[p * 2] != 0){
		print(p * 2);
	}
	if(tree[p * 2 + 1] != 0){
		print(p * 2 + 1);
	}
	printf("%c", tree[p]);
}
int main(int argc, char const *argv[])
{
	scanf("%d", &n);
	len = pow(2, n);
	scanf("%s", str);
	dfs(0, len - 1, 1);
	print(1);
	return 0;
}