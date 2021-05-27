#include <stdio.h>
#include <string.h>
using namespace std;
const char CH[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
struct num
{
	int val[128];
	int len;
	num(){
		memset(val, 0, sizeof(val));
		len = 0;
	}
};
num add(num a, num b, int n){
	num c;
	c.len = a.len > b.len ? a.len : b.len;
	int x = 0;
	for(int i = 1; i <= c.len; i ++){
		c.val[i] = a.val[i] + b.val[c.len - i + 1] + x;
		x = c.val[i] / n;
		c.val[i] %= n;
	}
	if(x > 0)
		c.val[++ c.len] = x;
	return c;
}
bool isR(num a){
	for(int i = 1; i <= a.len; i ++){
		int j = a.len - i + 1;
		if(a.val[i] != a.val[j])
			return false;
	}
	return true;
}
int n;
num a;
int main(int argc, char const *argv[])
{
	scanf("%d", &n);
	char in[128];
	scanf("%s", in);
	int len = strlen(in);
	for(int i = 0; i < len; i ++)
		a.val[++ a.len] = in[len - i - 1] > '9' ? in[len - i - 1] - 'A' + 10 : in[len - i - 1] - '0';
	for(int i = 0; i <= 30; i ++){
		if(isR(a)){
			printf("STEP=%d", i);
			return 0;
		}
		a = add(a, a, n);
	}
	printf("Impossible!");
	return 0;
}