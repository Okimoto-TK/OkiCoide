#include <stdio.h>
#include <string>
using namespace std;
unsigned long long sum;
char in[100000002];
const int M = 10000;
int main(int argc, char const *argv[])
{
	scanf("%s", in);
	string a = in;
	unsigned long long times = 1;
	bool t = false;
	unsigned long long num = 0;
	for(int i = 0; i < a.size(); i ++){
		if(a[i] == '+'){
			if(t){
				sum += (times * num) % M;
				t = false;
			}
			else
				sum += num % M;
			num = 0;
			times = 1;
		}
		else if(a[i] == '*'){
			times *= num;
			times %= M;
			t = true;
			num = 0;
		}
		else{
			num *= 10;
			num += a[i] - '0';
		}
		sum %= M;
	}
	if(t)\
		sum += (times * num) % M;
	else
		sum += num % M;
	sum %= M;
	printf("%llu", sum);
	return 0;
}