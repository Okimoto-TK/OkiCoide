#include <stdio.h>
#include <deque>
using namespace std;
long long n, k;
long long a[1000007];
deque <long long> d;
bool init = false;;
int main(int argc, char const *argv[])
{
	scanf("%lld%lld", &n, &k);
	for(long long i = 0; i < n; i ++)
		scanf("%lld", &a[i]);
	for(long long i = 0; i < n; i ++){
		if(!init){
			d.push_back(i);
			init = true;
		}
		else{
			while(!d.empty() && a[i] <= a[d.back()])
				d.pop_back();
			d.push_back(i);
			if(d.front() < i - k + 1)
				d.pop_front();
		}
		if(i >= k - 1)
			printf("%lld ", a[d.front()]);
	}
	printf("\n");
	init = false;
	d.clear();
	for(long long i = 0; i < n; i ++){
		if(!init){
			d.push_back(i);
			init = true;
		}
		else{
			while(!d.empty() && a[i] >= a[d.back()])
				d.pop_back();
			d.push_back(i);
			if(d.front() < i - k + 1)
				d.pop_front();
		}
		if(i >= k - 1)
			printf("%lld ", a[d.front()]);
	}
	return 0;
}