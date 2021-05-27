#include <stdio.h>
#include <math.h>
using namespace std;
long long n, k;
long long tree[100001];
bool check(long long mid){
	long long ans = 0;
	for(long long i = 0; i < n; i ++){
		long long sum = 0;
		while(sum + mid <= tree[i]){
			sum += mid;
			ans ++;
		}
	}
	return ans >= k;
}
int main(int argc, char const *argv[])
{
	scanf("%lld %lld", &n, &k);
	long long sum = 0;
	for(long long i = 0; i < n; i ++){
		scanf("%lld", &tree[i]);
		sum += tree[i];
	}
	if(sum < k){
		printf("0");
		return 0;
	}
	long long l = 1;
	long long r = sum;
	long long ans;
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