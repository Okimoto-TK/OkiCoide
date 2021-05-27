#include <stdio.h>
long long d, a1, a2, n;
int main()
{
    scanf("%lld%lld%lld", &a1, &a2, &n);
    d = a2 - a1;
    long long c = a1 - d;
    printf("%lld", (long long)(a1 + n * d + c) * n / 2);
    return 0;
}
