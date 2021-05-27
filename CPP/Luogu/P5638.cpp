#include <stdio.h>
using namespace std;
int n, k;
long long a[1000006];
int main(int argc, char const *argv[])
{
	scanf("%d %d", &n, &k);
	for(int i = 0; i < n - 1; i ++)
		scanf("%lld", &a[i]);
	long long max = 0, jmp;
	long long sum = 0;
	for(int i = 0; i < n - k; i ++){
		if(i == 0){
			for(int j = 0; j < k; j ++){
				sum += a[i + j];
			}
		}
		else{
			sum -= a[i - 1];
			sum += a[i + k - 1];
		}
		if(sum > max){
			max = sum;
			jmp = i;
		}
	}
	int pos = 1;
	long long ans = 0;
	while(pos < n){
		if(k != 0 && pos == jmp + 1){
			pos = jmp + k + 1;
			continue;
		}
		ans += a[pos - 1];
		pos ++;
	}
	printf("%lld", ans);
	return 0;
}