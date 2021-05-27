#include <stdio.h>
using namespace std;
int bucket[256];
int n, k;
char in[256];
int main(int argc, char const *argv[])
{
	scanf("%d %d", &n, &k);
	scanf("%s", in);
	for(int i = 0; i < n; i ++){
		bucket[in[i]] ++;
	}
	for(int i = 0; i < 256; i ++){
		if(bucket[i] > k){
			printf("NO");
			return 0;
		}
	}
	printf("YES");
	return 0;
}