#include <stdio.h>
#include <map>
using namespace std;
int main(int argc, char const *argv[])
{
	long long n, c;
	map <long long, long long> mp;
	scanf("%lld %lld", &n, &c);
	for(long long i = 0; i < n; i ++){
		long long x;
		scanf("%lld", &x);
		if(mp.find(x) != mp.end()){
			mp[x] += 1;
		}
		else{
			mp[x] = 1;
		}
	}
	long long ans = 0;
	for(map <long long, long long> :: iterator it = mp.begin(); it != mp.end(); it ++){
		long long x = it -> first - c;
		if(mp.find(x) != mp.end()){
			ans += mp[x] * (it -> second);
		} 
	}
	printf("%lld", ans);
	return 0;
}