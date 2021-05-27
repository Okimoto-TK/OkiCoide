#include <stdio.h>
#include <algorithm>
using namespace std;
int m, n;
int sch[100003];
int stu[100003];
int half(int left, int right, int x){
	if(left > right){
		int q = 1000000;
		int p;
		for(int i = -3; i <= 3; i ++){
			int a = abs(sch[right + i] - x);
			if(a < q){
				q = a;
				p = right + i; 
			}
		}
		if(p <= 0)
			return 1;
		return p;
	}
	int mid = (left + right) / 2;
	if(sch[mid] == x)
		return mid;
	if(sch[mid] > x)
		return half(left, mid - 1, x);
	if(sch[mid] < x)
		return half(mid + 1, right, x);
}
int main(int argc, char const *argv[])
{
	scanf("%d %d", &m, &n);
	for(int i = 1; i <= m; i ++)
		scanf("%d", &sch[i]);
	sort(sch, sch + 1 + m);
	for(int i = 1; i <= n; i ++)
		scanf("%d", &stu[i]);
	int ans = 0;
	for(int i = 1; i <= n; i ++){
		ans += abs(stu[i] - sch[half(1, m, stu[i])]);
	}
	printf("%d", ans);
	return 0;
}