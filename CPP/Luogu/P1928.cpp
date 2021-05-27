#include <stdio.h>
#include <string>
using namespace std;
string str;
int dp(int ptr){
	while(str[ptr] != ']' && ptr != str.size()){
		if(str[ptr] == '['){
			int times;
			int temp;
			if(str[ptr + 2] <= '9' && str[ptr + 2] >= '0'){
				times = 10 * (str[ptr + 1] - '0') + (str[ptr + 2] - '0');
				for(int i = 0; i < times; i ++)
					temp = dp(ptr + 3);
				ptr = temp;
			}else{
				times = str[ptr + 1] - '0';
				for(int i = 0; i < times; i ++)
					temp = dp(ptr + 2);
				ptr = temp;
			}
		}
		else{
			printf("%c", str[ptr]);
			ptr ++;
		}
	}
	return ptr + 1;
}
int main(int argc, char const *argv[])
{
	char in[20010];
	scanf("%s", in);
	str = in;
	dp(0);
	return 0;
}