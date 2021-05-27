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
char s[10007];
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
	int i = 1;
	while(scanf("%s", s) != EOF){
		init();
		while(true){
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
			scanf("%s", s);
			if(s[0] - '0' == 9 && strlen(s) == 1)
				break;
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
				printf("Set %d is not immediately decodable\n", i);
				goto endLoop;
			}
		}
		printf("Set %d is immediately decodable\n", i);
		endLoop:
			i ++;
	}
	return 0;
}