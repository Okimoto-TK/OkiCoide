#include <stdio.h>
#include <algorithm>
#include <set>
#pragma GCC optimize(2)
using namespace std;
int a[200009];
int n;
set <int> s;
bool cmp(int a, int b){
	return a > b;
}
int main(int argc, char const *argv[])
{
	scanf("%d", &n);
	for(int i = 0; i < n; i ++){
		int ai;
		scanf("%d", &ai);
		s.insert(ai);
	}
	int ss = s.size();
	for(int i = 0; i < ss; i ++){
		a[i] = *s.begin();
		s.erase(s.begin());
	}
	if(ss < 2){
		printf("-1");
		return 0;
	}
	sort(a, a + n, cmp);
	printf("%d", max(a[0] % a[1], a[2]));
	return 0;
}