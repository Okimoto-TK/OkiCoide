#include <stdio.h>
using namespace std;
int ans;
int n;
int main(int argc, char const *argv[])
{
	scanf("%d", &n);
	for(int i = 0; i < n; i ++){
		char str[100];
		scanf("%s", str);
		if(str[0] == 'I')
			ans += 20;
		else if(str[0] == 'D')
			ans += 12;
		else if(str[0] == 'O')
			ans += 8;
		else if(str[0] == 'C')
			ans += 6;
		else
			ans += 4;
	}
	printf("%d", ans);
	return 0;
}