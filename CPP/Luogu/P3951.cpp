#include <stdio.h>
using namespace std;
long long a, b;
int main()
{
    scanf("%lld%lld", &a, &b);
    printf("%lld", a * b - a - b);
    return 0;
}
