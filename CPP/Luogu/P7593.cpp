#include <stdio.h>
using namespace std;
void fun()
{
    long long n, k, s;
    scanf("%lld%lld%lld", &n, &k, &s);
    if((k + 1) * k / 2 > s || (n + n - k + 1) * k / 2 < s)
    {
        printf("No\n");
    }
    else
    {
        printf("Yes\n");
    }
}
int main()
{
    int T;
    for(scanf("%d", &T); T; T--)
    {
        fun();
    }
    return 0;
}
