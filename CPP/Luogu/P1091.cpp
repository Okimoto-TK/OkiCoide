#include <stdio.h>
using namespace std;
int n;
int t[128];
int ff[128];
int fb[128];
int getMax(int a, int b){
	return a > b ? a : b;
}
int main(int argc, char const *argv[])
{
	scanf("%d", &n);
	for(int i = 0; i < n; i ++)
		scanf("%d", &t[i]);
	for(int i = 0; i < n; i ++){
		int max = 0;
		for(int j = 0; j < i; j ++){
			if(t[j] < t[i])
				max = getMax(max, ff[j]);
		}
		ff[i] = max + 1;
	}
	for(int i = n - 1; i >= 0; i --){
		int max = 0;
		for(int j = n - 1; j > i; j --){
			if(t[j] < t[i])
				max = getMax(max, fb[j]);
		}
		fb[i] = max + 1;
	}
	int max = 0;
	for(int i = 0; i < n; i ++)
		max = getMax(max, ff[i] + fb[i]);
	printf("%d", n - max + 1);
	return 0;
}