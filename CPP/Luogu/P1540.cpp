#include <stdio.h>
#include <queue>
using namespace std;
int ram[1024];
queue <int> q;
int m, n;
int ans;
int main(int argc, char const *argv[])
{
	scanf("%d%d", &m, &n);
	for(int i = 0; i < n; i ++){
		int a;
		scanf("%d", &a);
		if(ram[a])
			continue;
		else{
			q.push(a);
			ram[a] = true;
			ans ++;
			if((int)q.size() > m){
				ram[q.front()] = false;
				q.pop();
			}
		}
	}
	printf("%d", ans);
	return 0;
}