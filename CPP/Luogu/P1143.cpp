#include <stdio.h>
#include <string.h>
#include <stack>
using namespace std;
int n;
char num[64];
int m;
stack <int> a;
int toTen(){
	int mtp = 1;
	for(int i = 0; i < strlen(num) - 1; i ++){
		mtp *= n;
	}
	int sum = 0;
	for(int i = 0; i < strlen(num); i ++){
		sum += mtp * (num[i] - '0');
		mtp /= n;
	}
	return sum;
}
void toN(int x){
	if(x == 0)
		return;
	a.push(x % m);
	x /= m;
	toN(x);
}
int main(int argc, char const *argv[])
{
	scanf("%d", &n);
	scanf("%s", num);
	for(int i = 0; i < strlen(num); i ++){
		if('0' <= num[i] && num[i] <= '9')
			continue;
		num[i] -= 7;
	}
	scanf("%d", &m);
	toN(toTen());
	while(!a.empty()){
		char c = a.top() + '0';
		a.pop();
		if(!('0' <= c && c <= '9'))
			c += 7;
		printf("%c", c);
	}
	return 0;
}