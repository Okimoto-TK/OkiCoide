#include <stdio.h>
#include <string>
using namespace std;
string s;
char in[64];
unsigned long long p, len, pw2;
int main(int argc, char const *argv[])
{
	scanf("%s", in);
	s = in;
	len = s.size();
	scanf("%llu", &p);
	for(pw2 = 1; pw2 * len < p; pw2 *= 2)
		continue;
	unsigned long long mid = pw2 * len / 2;
	while(p > len){
		if(mid > p){
			mid /= 2;
			continue;
		}
		p -= 1;
		if(p == mid){
			mid /= 2;
			continue;
		}
		if(p > mid)
			p -= mid;
		mid /= 2;
	}
	printf("%c", s[p - 1]);
	return 0;
}