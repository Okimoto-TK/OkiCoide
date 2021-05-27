#include <stdio.h>
using namespace std;
int n, w, s;
long long a[5502];
long long f[5502];
long long getMax(long long a, long long b){
	return a > b ? a : b;
}
long long getMin(long long a, long long b){
	return a < b ? a : b;
}
int main(int argc, char const *argv[])
{
	for(int i = 0; i < 5502; i ++)
		f[i] = -9999999999999999;
	scanf("%d %d %d", &n, &w, &s);
	for(int i = 0; i < n; i ++)
		scanf("%lld", &a[i]);
	f[1] = a[0];
	for(int i = 1; i < n; i ++){
		long long r[5502];
		for(int i = 0; i < 5502; i ++)
			r[i] = -9999999999999999;
		for(int j = 1; j <= w && j <= i; j ++){
			for(int k = getMin(w, j + 1); k >= getMax(1, j - s + 1); k --){
				if(r[k] < f[j] + k * a[i])
					r[k] = f[j] + k * a[i];
				else
					break;
			}
		}
		for(int j = 0; j < 5502; j ++)
			f[j] = r[j];
	}
	long long ans = -9999999999999999;
	for(int i = 0; i < 5502; i ++){
		ans = getMax(ans, f[i]);
	}
	printf("%lld", ans);
	return 0;
}