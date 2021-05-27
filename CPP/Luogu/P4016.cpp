#include <stdio.h>
#include <algorithm>
using namespace std;
int n;
long long avr;
long long a[1000007];
long long s[1000007];
int main()
{
    while(scanf("%d", &n) != EOF)
    {
        avr = 0;
        for(int i = 1; i <= n; i++)
        {
            scanf("%lld", &a[i]);
            avr += a[i];
        }
        avr /= n;
        for(int i = 1; i <= n; i++)
        {
            a[i] -= avr;
            s[i] = s[i - 1] + a[i];
        }
        sort(s + 1, s + 1 + n);
        long long k = s[(1 + n) / 2];
        long long ans = 0;
        for(int i = 1; i <= n; i++)
        {
            ans += abs(s[i] - k);
        }
        printf("%lld\n", ans);
    }
    return 0;
}
