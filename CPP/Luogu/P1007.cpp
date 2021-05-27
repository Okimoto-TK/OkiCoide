#include <stdio.h>
using namespace std;
struct sdr
{
	int pos;
	int dir;
};
int l;
int n;
int main(int argc, char const *argv[])
{
	scanf("%d", &l);
	scanf("%d", &n);
	int max = 0;
	int min = 0;
	for(int i = 0; i < n; i ++){
		int tmp;
		scanf("%d", &tmp);
		int a = tmp;
		int b = l - tmp + 1;
		if(a > b){
			max = max > a ? max : a;
			min = min > b ? min : b;
		}
		else{
			max = max > b ? max : b;
			min = min > a ? min : a;
		}
	}
	printf("%d %d", min, max);
	return 0;
}