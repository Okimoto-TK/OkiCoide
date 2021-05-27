#include <stdio.h>
#include <string.h>
using namespace std;
struct hInt
{
	int val[2000];
	int len;
	hInt(){
		memset(val, 0, sizeof(val));
		len = 0;
	}
	void print(){
		for(int i = len; i >= 1; i --)
			printf("%d", val[i]);
	}
};
hInt plusOne(hInt a){
	int x = 0;
	a.val[1] += 1;
	for(int i = 1; i <= a.len; i ++){
		a.val[i] += x;
		x = a.val[i] / 10;
		a.val[i] %= 10; 
		if(x == 0)
			break;
	}
	if(x > 0)
		a.val[++ a.len] = x;
	return a;
}
hInt timesTwo(hInt a){
	int x = 0;
	for(int i = 1; i <= a.len; i ++){
		a.val[i] *= 2;
		a.val[i] += x;
		x = a.val[i] / 10;
		a.val[i] %= 10;
	}
	if(x > 0)
		a.val[++ a.len] = x;
	return a;
}
int n;
hInt f[256];
int main(int argc, char const *argv[])
{
	scanf("%d", &n);
	f[1].val[1] = 1;
	f[1].len = 1;
	for(int i = 2; i <= n; i ++)
		f[i] = plusOne(timesTwo(f[i - 1]));
	timesTwo(f[n]).print();
	return 0;
}