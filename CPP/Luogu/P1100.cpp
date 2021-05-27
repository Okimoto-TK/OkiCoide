#include <stdio.h>
#include <stack>
#include <math.h>
using namespace std;
unsigned int n;
stack <int> a;
int len = -1;
void toTwo(unsigned int x){
	if(x == 0){
		len ++;
		return;
	}
	a.push(x % 2);
	x /= 2;
	len ++;
	toTwo(x);
}
int main(int argc, char const *argv[])
{
	scanf("%u", &n);
	toTwo(n);
	for(int i = len; i < 32; i ++)
		a.push(0);
	unsigned int sum = 0;
	for(int i = 15; i >= 0; i --){
		int t = a.top();
		a.pop();
		sum += t * pow(2, i);
	}
	for(int i = 31; i >= 16; i --){
		int t = a.top();
		a.pop();
		sum += t * pow(2, i);
	}
	printf("%u", sum);
	return 0;
}