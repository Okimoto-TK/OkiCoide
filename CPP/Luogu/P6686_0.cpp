#include <stdio.h>
#pragma GCC optimize(3)
using namespace std;
int main(int argc, char const *argv[])
{
	freopen("tab.txt", "w", stdout);
	for(long long i = 0; i <= 10000; i ++){
		printf("%lld, ", i * (i - 1) / 2);
	}
	return 0;
}