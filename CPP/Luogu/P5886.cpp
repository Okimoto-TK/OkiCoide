#include <stdio.h>
using namespace std;
int n, m, p;
short bucket[1000001];
int ans[1000001];
int ptr = 0;
int main(int argc, char const *argv[])
{
	scanf("%d %d %d", &n, &m, &p);
	for(int i = 0; i < n; i ++){
		int k;
		scanf("%d", &k);
		for(int j = 0; j < k; j ++){
			int in;
			scanf("%d", &in);
			bucket[in] ++;
		}
	}
	for(int i = 1; i <= m; i ++){
		if(bucket[i] == p){
			ans[ptr ++] = p;
		}
	}
	printf("%d\n", ptr);
	for(int i = 0; i < ptr; i ++)
		printf("%d ", ans[i]);
	return 0;
}