#include <stdio.h>
using namespace std;
long long k, n, w;
int main(int argc, char const *argv[])
{
    scanf("%lld%lld%lld", &k, &n, &w);
    long long sum = 0;
    for(int i = 1; i <= w; i ++)
        sum += i * k;
    printf("%lld\n", sum - n >= 0 ? sum - n : 0);
    return 0;
}