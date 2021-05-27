#include <stdio.h>
using namespace std;
struct node
{
	int dat;
	int rc;
	int lc;
};
node tree[1000100];
int max = -1;
int ans;
int n;
int count(int r){
	int rtn = 1;
	if(tree[r].rc != -1)
		rtn += count(tree[r].rc);
	if(tree[r].lc != -1)
		rtn += count(tree[r].lc);
	return rtn;
}
bool find(int r, int l){
	if(tree[r].dat != tree[l].dat) return false;
	if(r == -1 && l == -1) return true;
	return find(tree[r].lc, tree[l].rc) && find(tree[r].rc, tree[l].lc);
}
int main(int argc, char const *argv[])
{
	scanf("%d", &n);
	for(int i = 1; i <= n; i ++){
		scanf("%d", &tree[i].dat);
	}
	for(int i = 1; i <= n; i ++){
		scanf("%d %d", &tree[i].lc, &tree[i].rc);
	}
	for(int i = 1; i <= n; i ++){
		if(find(tree[i].rc, tree[i].lc)){
			int cnt = count(i);
			if(cnt > max){
				max = cnt;
				ans = i;
			}
		}
	}
	printf("%d", max);
	return 0;
}