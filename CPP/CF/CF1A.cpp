#include <stdio.h>
#include <math.h>
using namespace std;
long long n, m, a;
int main(int argc, char const *argv[])
{
	scanf("%lld %lld %lld", &n, &m, &a);
	printf("%lld", (long long)(ceil(double(n) / a)) * (long long)(ceil(double(m) / a)));
	return 0;
}