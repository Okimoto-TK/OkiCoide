#include <stdio.h>
using namespace std;
long long n, k;
int main(int argc, char const *argv[])
{
	scanf("%lld %lld", &n, &k);
	bool win = (n / k) % 2 == 1;
	printf("%s", win ? "YES" : "NO");
	return 0;
}