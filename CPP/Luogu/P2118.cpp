#include <stdio.h>
using namespace std;
int gcd(int a, int b){
	if(a % b == 0)
		return b;
	else
		return gcd(b, a % b);
}
int a;
int b;
int l;
int _a;
int _b;
double min = 9999.0;
int main(int argc, char const *argv[])
{
	scanf("%d%d%d", &a, &b, &l);
	for(int i = 1; i <= l; i ++){
		for(int j = 1; j <= l; j ++){
			if(gcd(i, j) == 1 && double(i) / double(j) >= double(a) / double(b) && double(i) / double(j) - double(a) / double(b)< min){
				_a = i;
				_b = j;
				min = double(i) / double(j) - double(a) / double(b);
			}
		}
	}
	printf("%d %d", _a, _b);
	return 0;
}