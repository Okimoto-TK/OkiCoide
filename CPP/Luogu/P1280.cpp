#include <stdio.h>
#include <vector>
using namespace std;
struct work
{
	int begin;
	int last;
	int end;
};
work w[10001];
vector <int> beg[10001];
int n, k;
int f[10001];
bool cmp(work a, work b){
	return a.begin < b.begin;
}
int getMin(int a, int b){
	return a < b ? a : b;
}
int main(int argc, char const *argv[])
{
	scanf("%d %d", &n, &k);
	for(int i = 0; i < k; i ++){
		scanf("%d %d", &w[i].begin, &w[i].last);
		w[i].end = w[i].begin + w[i].last - 1;
		beg[w[i].begin].push_back(i);
	}
	f[n + 1] = 0;
	for(int i = n; i >= 1; i --){
		if(beg[i].size() == 0)
			f[i] = f[i + 1];
		else{
			int min = 10000000;
			for(int j = 0; j < beg[i].size(); j ++){
				min = getMin(min, w[beg[i][j]].last + f[w[beg[i][j]].end + 1]);
			}
			f[i] = min;
		}
	}
	printf("%d", n - f[1]);
	return 0;
}