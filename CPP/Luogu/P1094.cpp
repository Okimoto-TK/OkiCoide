#include <iostream>
#include <algorithm>
using namespace std;
bool cmp(int x, int y){
	return x > y;
}
int main(int argc, char const *argv[])
{
	int w;
	int n;
	cin >> w;
	cin >> n;
	int p[n];
	bool t[n];
	for(int i = 0; i < n; i ++){
		cin >> p[i];
		t[i] = false;
	}
	sort(p, p + n, cmp);
	int ans = 0;
	int ptr = 0;
	while(ptr < n){
		if(t[ptr]){
			ptr ++;
			continue;
		}
		ans ++;
		t[ptr] = true;
		int i;
		for(i = 0; i < n; i ++){
			if(p[i] <= w - p[ptr] && !t[i]){
				break;
			}
		}
		if(i != n){
			t[i] = true;
		}
		ptr ++;
	}
	cout << ans;
	return 0;
}