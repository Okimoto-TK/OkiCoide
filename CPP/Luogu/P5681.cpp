#include <stdio.h>
#pragma GCC optimize(2)
using namespace std;
long long a, b, c;
int main(int argc, char const *argv[])
{
	scanf("%lld %lld %lld", &a, &b, &c);
	printf("%s", a * a > b * c ? "Alice" : "Bob");
	return 0;
}