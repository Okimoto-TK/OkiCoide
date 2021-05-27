#include <stdio.h>
#include <algorithm>
using namespace std;
long long n, p;
long long a[100007];
long long b[100007];
bool check(double x)
{
    double eng = p;
    double t = 0;
    for(int i = 1; i <= n; i++)
    {
        t += min(double(b[i]) / x - a[i], 0.0);
    }
    return t + eng >= -0.000001;
}
int main()
{
    scanf("%lld%lld", &n, &p);
    for(int i = 1; i <= n; i++)
    {
        scanf("%lld%lld", &a[i], &b[i]);
    }
    double l = 0;
    double r = ((unsigned long long)1 << 63) - 1ll;
    double ans = -1;
    while(l < r)
    {
        double mid = (l + r) / 2;
        if(check(mid))
        {
            ans = mid;
            l = mid + 0.00001;
        }
        else
        {
            r = mid - 0.00001;
        }
    }
    if(ans == ((unsigned long long)1 << 63) - 1ll)
    {
        printf("-1");
        return 0;
    }
    printf("%.5f", ans);
    return 0;
}
