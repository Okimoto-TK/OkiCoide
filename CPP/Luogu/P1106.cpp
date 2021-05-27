#include <stdio.h>
#include <string.h>
using namespace std;
char a[256];
char o[256];
int k;
int main(int argc, char const *argv[])
{
	scanf("%s", a);
	scanf("%d", &k);
	int aft = strlen(a) - k;
	int pro = 0;
	int ptr = 0;
	while(pro < aft){
		int min = 10;
		int sub;
		int tmp;
		for(int i = ptr; i <= ptr + k; i ++){
			if(a[i] - '0' < min){
				min = a[i] - '0';
				o[pro] = min + '0';
				sub = i - ptr;
				tmp = i;
			}
		}
		pro ++;
		ptr = tmp + 1;
		k -= sub;
	}
	o[pro] = '\0';
	bool flg = true;
	for(int i = 0;i < strlen(o); i ++){
		if(flg && o[i] == '0')
			continue;
		flg = false;
		printf("%c", o[i]);
	}
	if(flg)
		printf("0");
	return 0;
}