#include <stdio.h>
using namespace std;
int n;
int main(int argc, char const *argv[])
{
	scanf("%d", &n);
	int a;
	int seq[2 * n + 2];
	for(a = 0; a < n; a ++)
		seq[a] = 1;
	for(a = n + 2; a < 2 * n + 2; a ++)
		seq[a] = 2;
	int left = n;
	int mid = n;
	int last = 2 * n + 2;
	while(left > 3){
		seq[mid] = seq[last - 2];
		seq[mid + 1] = seq[last - 1];
		seq[last - 2] = 0;
		seq[last - 1] = 0;
		for(int i = 0; i < 2 * n + 2; i ++)
			printf("%c", seq[i] == 0 ? '-' : (seq[i] == 1 ? 'o' : '*'));
		printf("\n");
		seq[last - 2] = seq[mid - 1];
		seq[last - 1] = seq[mid];
		seq[mid - 1] = 0;
		seq[mid] = 0;
		for(int i = 0; i < 2 * n + 2; i ++)
			printf("%c", seq[i] == 0 ? '-' : (seq[i] == 1 ? 'o' : '*'));
		printf("\n");
		last -= 2;
		mid -= 1;
		left -= 1;
	}
	printf("ooo*o**--*");
	for(int i = 0; i < n - 4; i ++)
		printf("o*");
	printf("\no--*o**oo*");
	for(int i = 0; i < n - 4; i ++)
		printf("o*");
	printf("\no*o*o*--o*");
	for(int i = 0; i < n - 4; i ++)
		printf("o*");
	printf("\n--o*o*o*o*");
	for(int i = 0; i < n - 4; i ++)
		printf("o*");
	return 0;
}