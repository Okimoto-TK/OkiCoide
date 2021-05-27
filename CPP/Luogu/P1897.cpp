#include <stdio.h>
#include <algorithm>
using namespace std;
int n;
int a[100007];
int b[20000007];
int main()
{
    scanf("%d", &n);
    for(int i = 1; i <= n; i++)
    {
        scanf("%d", &a[i]);
        b[a[i]]++;
    }
    sort(a + 1, a + 1 + n);
    int ans = 10 * a[n];
    for(int i = 0; i <= 20000007; i++)
    {
        ans += b[i] ? 5 + b[i] : 0;
    }
    printf("%d", ans);
    return 0;
}
