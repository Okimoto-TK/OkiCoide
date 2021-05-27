#include <stdio.h>
#include <queue>
#pragma GCC optimize(2)
using namespace std;
int n, m;
queue <int> q;
int tap[128];
bool st[128];
bool fn[128];
int main(int argc, char const *argv[])
{
	scanf("%d %d", &n, &m);
	for(int i = 0; i < n; i ++){
		int t;
		scanf("%d", &t);
		q.push(t);
	}
	int cnt = 0;
	int ans = -1;
	while(cnt < n){
		ans ++;
		for(int i = 0; i < m; i ++){
			tap[i] -= 1;
			if(tap[i] == 0 || tap[i] == -1){
				if(!q.empty()){
					tap[i] = q.front();
					q.pop();
				}
				else
					fn[i] = true;
				if(st[i])
					cnt ++;
				if(!fn[i])
					st[i] = true;
				else
					st[i] = false;
			}
		}
	}
	printf("%d", ans);
	return 0;
}