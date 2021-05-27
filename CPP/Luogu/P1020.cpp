#include <stdio.h>
using namespace std;
int a[100001];
int s[100001];
int m[100001];
int ans;
int ptr;
int n;
int half(int x, int l, int r){
	while(l < r){
		int mid = (l + r) / 2;
		if(s[mid] >= x)
			l = mid + 1;
		else
			r = mid;
	}
	return r;
}
int half(int x, int l, int r, int p){
	while(l <= r){
		int mid = (l + r) / 2;
		if(s[mid] == x)
			return mid;
		if(s[mid] < x)
			l = mid + 1;
		else
			r = mid - 1;
	}
	return l;
}
int main(int argc, char const *argv[])
{
	int t;
	while(scanf("%d", &t) != EOF)
		a[n ++] = t;
	s[0] = a[0];
	ptr ++;
	for(int i = 1; i < n; i ++){
		if(a[i] <= s[ptr - 1])
			s[ptr ++] = a[i];
		else{
			int j = half(a[i], 0, ptr - 1);
			s[j] = a[i];
		}
	}
	m[0] = a[0];
	ans ++;
	for(int i = 1; i < n; i ++){
		if(a[i] > s[ans - 1])
			s[ans ++] = a[i];
		else{
			int j = half(a[i], 0, ans - 1, 233);
			s[j] = a[i];
		}
	}
	printf("%d\n%d", ptr, ans);
	return 0;
}