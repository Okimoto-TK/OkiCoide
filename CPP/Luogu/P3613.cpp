#include <stdio.h>
#include <vector>
#include <map>
using namespace std;
map <int, int> v[100001];
int main(int argc, char const *argv[])
{
	int ans[100001];
	int ptr = 0;
	int n, q;
	scanf("%d %d", &n, &q);
	for(int a = 0; a < q; a ++){
		int t;
		scanf("%d", &t);
		if(t == 1){
			int i, j, k;
			scanf("%d %d %d", &i, &j, &k);
			if(k == 0)
				v[i - 1].erase(j - 1);
			else
				v[i - 1].insert(pair<int, int>(j - 1, k));
		}
		else{
			int i, j;
			scanf("%d %d", &i, &j);
			ans[ptr ++] = v[i - 1][j - 1];
		}
	}
	for(int i = 0; i < ptr; i ++)
		printf("%d\n", ans[i]);
	return 0;
}