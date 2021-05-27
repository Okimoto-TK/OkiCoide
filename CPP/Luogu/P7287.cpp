#include <stdio.h>
#include <math.h>
#include <algorithm>
#include <string.h>
using namespace std;
long long n, a, b, s;
long long ans;
long long arr[100007];
long long buf[100007];
bool check(long long v)
{
    bool yes = false;
    for(long long i = 0; i <= 31; i++)
    {
        long long w = v - i * b;
        long long p = pow(2, i);
        long long x = w / a;
        if(w < 0){ continue; }
        for(long long j = 1; j <= n; j++)
        {
            buf[j] = arr[j] + x;
        }
        long long mx = 0;
        long long cmx = 0;
        for(long long j = 1; j <= n; j++)
        {
            if(cmx >= 0)
            {
                cmx += buf[j];
            }
            else
            {
                cmx = buf[j];
            }
            if(cmx > mx)
            {
                mx = cmx;
            }
        }
        yes |= ((mx * p) >= s);
    }
    return yes;
}
int main()
{
    scanf("%lld%lld%lld%lld", &n, &a, &b, &s);
    for(long long i = 1; i <= n; i++)
    {
        scanf("%lld", &arr[i]);
    }
    long long l = 0;
    long long r = 4000000000;
    while(l <= r)
    {
        long long mid = (l + r) >> 1;
        if(check(mid))
        {
            ans = mid;
            r = mid - 1;
        }
        else
        {
            l = mid + 1;
        }
    }
    printf("%lld", ans);
    return 0;
}
