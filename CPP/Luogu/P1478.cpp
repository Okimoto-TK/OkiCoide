#include <stdio.h>
#include <algorithm>
using namespace std;
struct apple
{
	int x;
	int y;
};
bool cmp(apple a, apple b){
	return a.y < b.y;
}
int main(int argc, char const *argv[])
{
	int n, s;
	scanf("%d %d", &n, &s);
	if(n <= 0 || s <= 0){
		printf("0");
		return 0;
	}
	int a, b;
	scanf("%d %d", &a, &b);
	int len = a + b;
	apple apples[n];
	for(int i = 0; i < n; i ++){
		scanf("%d %d", &apples[i].x, &apples[i].y);
	}
	sort(apples, apples + n, cmp);
	int ptr = 0;
	int ans = 0;
	while(ptr < n){
		if(apples[ptr].y > s){
			ptr ++;
			continue;
		}
		if(apples[ptr].x > len){
			ptr ++;
			continue;
		}
		s -= apples[ptr].y;
		ans += 1;
		ptr ++;
	}
	printf("%d", ans);
	return 0;
}