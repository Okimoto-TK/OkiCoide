#include <stdio.h>
#include <algorithm>
using namespace std;
struct dat
{
	unsigned long long val;
	unsigned long long a;
	unsigned long long b;
};
unsigned long long ptr;
dat q[100001];
unsigned long long zone[512][512];
unsigned long long max_[512];
unsigned long long n;
bool check(unsigned long long i, unsigned long long j){
	if(max_[i] == max_[j])
		return false;
	return true;
}
bool cmp(dat a, dat b){
	return a.val > b.val;
}
int main(int argc, char const *argv[])
{
	scanf("%lld", &n);
	for(unsigned long long i = 1; i < n; i ++){
		for(unsigned long long j = i + 1; j <= n; j ++){
			unsigned long long t;
			scanf("%lld", &t);
			zone[i][j] = t;
			zone[j][i] = t;
		}
	}
	for(unsigned long long i = 1; i <= n; i ++){
		unsigned long long mx_ = 0;
		for(unsigned long long j = 1; j <= n; j ++){
			if(zone[i][j] > mx_){
				mx_ = zone[i][j];
			}
		}
		max_[i] = mx_;
	}
	for(unsigned long long i = 1; i <= n; i ++){
		for(unsigned long long j = 1; j < i; j ++){
			if(i == j)
				continue;
			if(zone[i][j] == max_[i] && zone[i][j] == max_[j])
				continue;
			dat tmp;
			tmp.val = zone[i][j];
			tmp.a = i;
			tmp.b = j;
			q[ptr ++] = tmp;
		}
	}
	sort(q, q + ptr, cmp);
	for(unsigned long long i = 0; i < ptr; i ++){
		if(check(q[i].a, q[i].b)){
			printf("1\n");
			printf("%lld", q[i].val);
			return 0;
		}
	}
	printf("0");
	return 0;
}