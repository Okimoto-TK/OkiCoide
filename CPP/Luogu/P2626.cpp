#include <stdio.h>
#include <math.h>
#include <queue>
using namespace std;
long long f[50] = {1, 1};
const long long MOD = 2147483648;
queue <long long> ans;
int n;
int main(int argc, char const *argv[])
{
	scanf("%d", &n);
	n -= 1;
	for(int i = 2; i <= n; i ++){
		f[i] = (f[i - 1] + f[i - 2]) %MOD;
	}
	int _f = f[n];
	for(long long i = 2; i <= _f; i ++){
		while(f[n] % i == 0){
			f[n] /= i;
			ans.push(i);
		}
		if(f[n] == 1)
			break;
	}
	printf("%lld=", _f);
	if(f[n] > 1)
		ans.push(f[n]);
	while(!ans.empty()){
		printf("%lld", ans.front());
		ans.pop();
		if(!ans.empty())
			printf("*");
	}
	return 0;
}