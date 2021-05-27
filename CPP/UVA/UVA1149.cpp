#include <stdio.h>
#include <algorithm>
using namespace std;
int t;
int main(int argc, char const *argv[])
{
	scanf("%d", &t);
	for(int i = 0; i < t; i ++){
		int n;
		scanf("%d", &n);
		int v;
		scanf("%d", &v);
		int w[n + 1];
		bool f[n + 1];
		int ans = 0;
		for(int j = 0; j < n; j ++)
			f[j] = false;
		for(int j = 0; j < n; j ++)
			scanf("%d", &w[j]);
		sort(w, w + n);
		int cnt = 0;
		int ptr = 0;
		while(cnt < n){
			if(f[ptr]){
				ptr ++;
				continue;
			}
			int k;
			for(k = n - 1; k > ptr; k --){
				if(w[k] + w[ptr] <= v && !f[k])
					break;
			}
			if(k != ptr){
				f[k] = true;
				f[ptr ++] = true;
				cnt += 2;
				ans ++;
				continue;
			}
			else{
				f[ptr ++] = true;
				cnt ++;
				ans ++;
				continue;
			}
		}
		printf("%d\n", ans);
	}
	return 0;
}