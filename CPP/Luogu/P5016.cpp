#include <stdio.h>
using namespace std;
unsigned long long min = 100000000000000000000L;
int ans;
unsigned long long abs(unsigned long long a, unsigned long long b){
	return a > b ? a - b : b - a;
}
int main(int argc, char const *argv[])
{
	long long n;
	scanf("%lld", &n);
	long long cam[200000];
	for(long long i = 1; i <= n; i ++){
		scanf("%lld", &cam[i]);
	}
	long long m, p1, p2, s1, s2;
	scanf("%lld %lld %lld %lld", &m, &p1, &s1, &s2);
	cam[p1] += s1;
	long long a = 0;
	for(long long i = 1; i < m; i ++){
		a += cam[i] * (m - i);
	}
	long long b = 0;
	for( long long i = m + 1; i <= n; i ++){
		b += cam[i] * (i - m);
	}
	for( long long i = 1; i <= n; i ++){
		long long t =  s2 * abs(i, m);
		if(i < m){
			if(abs(a + t, b) < min){
				min = abs(a + t, b);
				ans = i;
			}
		}
		else if(m == i){
			if(abs(a, b) < min){
				min = abs(a, b);
				ans = i;
			}
		}
		else{
			if(abs(a, t + b) < min){
				min = abs(a, t + b);
				ans = i;
			}
		}
	}
	printf("%d", ans);
	return 0;
}