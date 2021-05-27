#include <stdio.h>
using namespace std;
int n;
const long long p = 1e9 + 7;
long long a[500007];
long long b[500007];
long long pa[500007];
long long pb[500007];
long long ppa[500007];
long long ppb[500007];
long long sab[500007];
int main()
{
    scanf("%d", &n);
    for(int i = 1; i <= n; i++)
    {
        scanf("%lld", &a[i]);
        pa[i] = pa[i - 1] % p + a[i] % p;
        pa[i] %= p;
    }
    for(int i = 1; i <= n; i++)
    {
        scanf("%lld", &b[i]);
        pb[i] = pb[i - 1] % p + b[i] % p;
        pb[i] %= p;
    }
    for(int i = n; i >= 1; i--)
    {
        (sab[i] = sab[i + 1] + pa[i] * pb[i] % p) %= p;
        (ppb[i] = ppb[i + 1] + pb[i]) %= p;
        (ppa[i] = ppa[i + 1] + pa[i]) %= p;
    }
    long long ans = 0;
    for(int i = 1; i <= n; i++)
    {
        (ans += sab[i] % p) %= p;
        (ans += (n - i + 1) * pa[i - 1] % p * pb[i - 1] % p) %= p;
        (ans -= pb[i - 1] * ppa[i] % p) %= p;
        (ans -= pa[i - 1] * ppb[i] % p) %= p;
    }
    printf("%lld", (ans + p) % p);
    return 0;
}
