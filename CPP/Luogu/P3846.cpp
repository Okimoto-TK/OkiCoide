#include <stdio.h>
#include <map>
#include <math.h>
using namespace std;
void exeuc(long long a, long long b, long long & d, long long & x, long long & y){
	if(b == 0){
		d = a;
		x = 1;
		y = 0;
		return;
	}
	exeuc(b, a % b, d, x, y);
	long long t = x;
	x = y;
	y = t - (a / b) * y;
}
void bsgs(long long a, long long b, long long p){
	a %= p;
	long long m = ceil(sqrt(p));
	long long t = 1;
	map <long long, long long> mp;
	mp[1] = m + 1;
	for(long long j = 1; j < m; j ++){
		t = t * a % p;
		if(!mp[t])
			mp[t] = j;
	}
	t = t * a % p;
	long long d = 1;
	long long g;
	long long x;
	long long y;
	for(long long i = 0; i < m; i ++){
		exeuc(d, p, g, x, y);
		x = (b / g * x % p + p) % (p / g);
		long long j = mp[x];
		if(j){
			if(j == m + 1)
				j = 0;
			printf("%lld\n", i * m + j);
			return;
		}
		d = d * t % p;
	}
	printf("no solution\n");
}
long long a, b, p;
int main(int argc, char const *argv[])
{
	scanf("%lld%lld%lld", &p, &a, &b);
	bsgs(a, b, p);
	return 0;
}