#include <stdio.h>
#include <string>
using namespace std;
int n;
bool flg = false;
string out = "";
int main(int argc, char const *argv[])
{
	scanf("%d", &n);
	char in[16];
	for(int i = 0; i < n; i ++){
		scanf("%s", in);
		if(!flg && in[0] == 'O' && in[1] == 'O'){
			in[0] = '+';
			in[1] = '+';
			flg = true;
		}
		else if(!flg && in[3] == 'O' && in[4] == 'O'){
			in[3] = '+';
			in[4] = '+';
			flg = true;
		}
		out += in;
		out += '\n';
	}
	if(!flg){
		printf("NO");
	}
	else{
		printf("YES\n");
		printf("%s", out.c_str());
	}
	return 0;
}