#include <stdio.h>
#include <map>
using namespace std;
long long n, m;
long long num[100005];
map <long long, map <long long, long long> > mp;
map <long long, map <long long, long long> > :: iterator it;
map <long long, long long> :: iterator it_;
long long getSum(long long x, long long y){
	long long sum = 0;
	it = mp.find(x);
	for(long long i = x; i <= y; i ++)
		sum += num[i];
	return sum;
}
bool check(long long mid){
	long long p1 = 0;
	long long p2 = 1;
	long long cnt = 0;
	do{
		long long sum;
		it = mp.find(p1);
		if(it != mp.end()){
			it_ = (it -> second).find(p2);
			if(it_ != (it -> second).end())
				sum = it_ -> second;
			else{
				it_ = (it -> second).find(p2 - 1);
				sum = it_ -> second + num[p2];
				(it -> second)[p2] = sum;
			}
		}
		else{
			sum = getSum(p1, p2);
			map <long long, long long> temp;
			temp[p2] = sum;
			mp.insert(mp.begin(), pair <long long, map <long long, long long> >(p1, temp));
		}
		if(sum < mid){
			p2 ++;
			continue;
		}
		else{
			p1 = p2 ++;
			cnt ++;
		}
	}while(p2 < n);
	printf("%d %d\n", cnt, m);
	return cnt < m;
}
inline long long read(){
    long long s = 0, w = 1; char ch = getchar();
    while(ch < '0' || ch > '9'){ if(ch == '-') w = -1; ch = getchar();}
    while(ch >= '0' && ch <= '9') s = s * 10 + ch - '0', ch = getchar();
    return s * w;
}
int main(int argc, char const *argv[])
{
	freopen("tab.txt", "r", stdin);
	long long sum = 0;
	scanf("%lld %lld", &n, &m);
	for(int i = 0; i < n; i ++){
		num[i] = read();
		sum += num[i];
	}
	long long l = 0;
	long long r = sum;
	printf("%lld\n", sum);
	long long ans;
	while(l <= r){
		long long mid = (l + r) / 2;
		printf("%lld\n", mid);
		if(check(mid)){
			printf("1\n");
			r = mid - 1;
		}
		else{
			ans = mid;
			l = mid + 1;
		}
	}
	printf("%lld", ans);
	return 0;
}