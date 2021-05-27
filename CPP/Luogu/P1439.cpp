#include <stdio.h>
using namespace std;
int a[100001];
int b[100001];
int m[100001];
int s[100001];
int ans;
int n;
int half(int x, int l, int r){
	while(l <= r){
		int mid = (l + r) / 2;
		if(s[mid] < x)
			l = mid + 1;
		else
			r = mid - 1;
	}
	return l;
}
int main(int argc, char const *argv[])
{
	scanf("%d", &n);
	for(int i = 0; i < n; i ++){
		scanf("%d", &a[i]);
		m[a[i]] = i;
	}
	for(int i = 0; i < n; i ++){
		scanf("%d", &b[i]);
		b[i] = m[b[i]];
	}
	s[0] = b[0];
	ans ++;
	for(int i = 1; i < n; i ++){
		if(b[i] > s[ans - 1])
			s[ans ++] = b[i];
		else{
			int j = half(b[i], 0, ans - 1);
			s[j] = b[i];
		}
	}
	printf("%d", ans);
	return 0;
}