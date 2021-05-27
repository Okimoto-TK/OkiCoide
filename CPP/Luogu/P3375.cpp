#include <stdio.h>
#include <string>
using namespace std;
int nxt[2000001] = {-1};
char in1[2000001];
char in2[2000001];
string s1;
string s2;
void getnxt(){
	int j = 0;
	int k = -1;
	while(j < s2.size()){
		if(k == -1 || s2[j] == s2[k]){
			k ++;
			j ++;
			nxt[j] = k;
		}
		else
			k = nxt[k];
	}
}
void kmp(){
	int i = 0;
	int j = 0;
	while(i <= s1.size()){
		if(j == s2.size()){
			printf("%d\n", i - j + 1);
			i ++;
			j = nxt[j];
		}
		if(j == -1 || s1[i] == s2[j]){
			i ++;
			j ++;
		}
		else{
			j = nxt[j];
		}
	}
}
int main(int argc, char const *argv[])
{
	scanf("%s", in1);
	scanf("%s", in2);
	s1 = in1;
	s2 = in2;
	getnxt();
	kmp();
	for(int i = 1; i <= s2.size(); i ++)
		printf("%d ", nxt[i]);
	return 0;
}