#include <stdio.h>
#include <algorithm>
using namespace std;
int n;
int a[100007];
int main()
{
    scanf("%d", &n);
    long long ans = 0;
    for(int i = 1; i <= n; i++)
    {
        scanf("%d", &a[i]);
        if(i != 1){ ans += max(a[i - 1], a[i]); }
    }
    printf("%lld", ans);
    return 0;
}
