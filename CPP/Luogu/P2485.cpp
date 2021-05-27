#include <stdio.h>
#include <math.h>
#include <map>
using namespace std;
long long fpow(long long x, long long k, long long p){
	long long r = 1;
	while(k != 0){
		if(k & 1 == 1)
			r = r * x % p;
		k >>= 1;
		x = x * x % p;
	}
	return r;
}
long long gcd(long long a, long long b){
	if(b == 0)
		return a;
	return gcd(b, a % b);
}
void exgcd(long long a, long long b, long long &d, long long &x, long long &y){
	if(b == 0){
		d = a;
		x = 1;
		y = 0;
		return;
	}
	exgcd(b, a % b, d, x, y);
	long long t = x;
	x = y;
	y = t - a / b * y;
}
map <long long, long long> mp;
void bsgs(long long a, long long b, long long p){
	long long m = ceil(sqrt(p));
	long long t = 1;
	mp.clear();
	a %= p;
	mp[1] = m + 1;
	for(long long j = 1; j < m; j ++){
		t = t * a % p;
		mp[t] = j;
	}
	t = t * a % p;
	long long _t = 1, d, x, y;
	for(long long i = 0; i < m; i ++){
		exgcd(_t, p, d, x, y);
		x = (b / d * x % p + p) % (p / d);
		long long j = mp[x];
		if(j != 0){
			if(j == m + 1)
				j = 0;
			printf("%lld\n", i * m + j);
			return;
		}
		_t = _t * t % p;
	}
	printf("Orz, I cannot find x!\n");
}
int main(int argc, char const *argv[])
{
	int t, k;
	scanf("%d%d", &t, &k);
	for(int i = 1; i <= t; i ++){
		if(k == 1){
			long long y, z, p;
			scanf("%lld%lld%lld", &y, &z, &p);
			printf("%lld\n", fpow(y, z, p));
		}
		else if(k == 2){
			long long x, y, a, b, p;
			scanf("%lld%lld%lld", &a, &b, &p);
			long long d = gcd(a, p);
			if(b % d != 0){
				printf("Orz, I cannot find x!\n");
				continue;
			}
			long long _a = a / d;
			long long _b = b / d;
			long long _p = p / d;
			exgcd(_a, _p, d, x, y);
			x = (x * _b % _p + _p) % _p;
			printf("%lld\n", x);
		}
		else{
			long long y, z, p;
			scanf("%lld%lld%lld", &y, &z, &p);
			if(y % p == 0){
				if(z % p == 1)
					printf("0\n");
				else if(z % p == 0)
					printf("1\n");
				else
					printf("Orz, I cannot find x!\n");
				continue;
			}
			bsgs(y, z, p);
		}
	}	
	return 0;
}