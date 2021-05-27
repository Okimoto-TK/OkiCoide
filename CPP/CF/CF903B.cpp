#include <stdio.h>
#include <queue>
using namespace std;
queue <bool> ans;
int h1, a1, c1;
int h2, a2;
int main(int argc, char const *argv[])
{
	scanf("%d %d %d", &h1, &a1, &c1);
	scanf("%d %d", &h2, &a2);
	while(h2 > 0){
		if(a1 >= h2){
			ans.push(true);
			h2 -= a1;
		}
		else if(a2 >= h1){
			ans.push(false);
			h1 += c1;
		}
		else{
			ans.push(true);
			h2 -= a1;
		}
		h1 -= a2;
	}
	printf("%d\n", ans.size());
	while(!ans.empty()){
		printf("%s\n", ans.front() ? "STRIKE" : "HEAL");
		ans.pop();
	}
	return 0;
}