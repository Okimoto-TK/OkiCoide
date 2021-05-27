#include <stdio.h>
#include <string.h>
using namespace std;
struct node
{
	int con[10];
	bool end;
	node(){
		for(int i = 0; i < 10; i ++)
			con[i] = -1;
		end = false;
	}
};
int p = 1;
int t;
node tree[100007];
void init(){
	for(int i = 0; i <= p; i ++){
		for(int j = 0; j < 10; j ++)
			tree[i].con[j] = -1;
		tree[i].end = false;
	}
	p = 1;
}
int main(int argc, char const *argv[])
{
	scanf("%d", &t);
	for(int i = 0; i < t; i ++){
		int n;
		init();
		scanf("%d", &n);
		for(int j = 0; j < n; j ++){
			char s[10007];
			scanf("%s", s);
			int at = 0;
			for(int k = 0; k < (int)strlen(s); k ++){
				if(tree[at].con[s[k] - '0'] != -1){
					at = tree[at].con[s[k] - '0'];
				}
				else{
					tree[at].con[s[k] - '0'] = p;
					at = p ++;
				}
			}
			tree[at].end = true;
		}
		for(int j = 1; j < p; j ++){
			bool son = false;
			for(int k = 0; k < 10; k ++){
				if(tree[j].con[k] != -1){
					son = true;
					break;
				}
			}
			if(son && tree[j].end){
				printf("NO\n");
				goto endLoop;
			}
		}
		printf("YES\n");
		endLoop:
			continue;
	}
	return 0;
}