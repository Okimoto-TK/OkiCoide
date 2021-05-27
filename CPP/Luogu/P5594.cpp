#include <stdio.h>
using namespace std;
int bucket[1001];
bool flg[1001][1001];
int main(int argc, char const *argv[])
{
	int n, m, k;
	scanf("%d %d %d", &n, &m, &k);
	for(int i = 0; i < n; i ++){
		for(int j = 0; j < m; j ++){
			int in;
			scanf("%d", &in);
			if(!flg[in][j + 1]){
				flg[in][j + 1] = true;
				bucket[in] ++;
			}
		}
	}
	for(int i = 1; i <= k; i ++)
		printf("%d ", bucket[i]);
	return 0;
}