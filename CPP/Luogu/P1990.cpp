#include <stdio.h>
using namespace std;
int tab[1000005] = {1, 1, 2, 5};
int main(int argc, char const *argv[])
{
	int n;
	scanf("%d", &n);
	if(n <= 3){
		printf("%d", tab[n]);
		return 0;
	}
	for(int i = 4; i <= n; i ++){
		tab[i] = 2 * tab[i - 1] % 10000 + tab[i - 3] % 10000;
        tab[i] %= 10000;
	}
	printf("%d", tab[n]);
	return 0;
}