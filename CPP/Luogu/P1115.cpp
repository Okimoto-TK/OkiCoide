#include <stdio.h>
using namespace std;
long long n;
long long a[200007];
long long sum[200007];
long long min[200007];
long long ans = -100000000000;
int main(int argc, char const *argv[])
{
	scanf("%lld", &n);
	for(long long i = 0; i < n; i ++)
		scanf("%lld", &a[i]);
	sum[0] = a[0];
	for(long long i = 1; i < n; i ++)
		sum[i] = sum[i - 1] + a[i];
	min[0] = a[0];
	for(long long i = 1; i < n; i ++)
		min[i] = min[i - 1] < sum[i] ? min[i - 1] : sum[i];
	for(long long i = 0; i < n; i ++)
		ans = ans > a[i] ? ans : a[i];
	for(long long i = 0; i < n; i ++)
		ans = ans > sum[i] ? ans : sum[i];
	for(long long i = 1; i < n; i ++)
		ans = ans > sum[i] - min[i - 1] ? ans : sum[i] - min[i - 1];
	printf("%lld", ans);
	return 0;
}