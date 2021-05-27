#include <stdio.h>
using namespace std;
long long n, m;
long long tree[1000001];
bool check(long long mid){
	long long ttl = 0;
	for(long long i = 0; i < n; i ++){
		if(tree[i] > mid)
			ttl += tree[i] - mid;
	}
	return ttl >= m;
}
int main(int argc, char const *argv[])
{
	long long max = -1;
	scanf("%lld %lld", &n, &m);
	for(long long i = 0; i < n; i ++){
		scanf("%lld", &tree[i]);
		if(tree[i] > max)
			max = tree[i];
	}
	long long l = 0;
	long long r = max;
	long long ans = 0;
	while(l <= r){
		long long mid = (l + r) / 2;
		if(check(mid)){
			ans = mid;
			l = mid + 1;
		}
		else{
			r = mid - 1;
		}
	}
	printf("%lld", ans);
	return 0;
}