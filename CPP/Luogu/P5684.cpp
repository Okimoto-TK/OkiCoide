#include <stdio.h>
#include <math.h>
#include <string.h>
#include <vector>
using namespace std;
const long long p = 1000000007;
long long n;
char buf[10007];
long long buk[32];
long long fact(long long x)
{
    long long r = 1;
    for(long long i = 1; i <= x; i++)
    {
        r = (i * r) % p;
    }
    return r;
}
int main()
{
    scanf("%d", &n);
    scanf("%s", buf);
    n = strlen(buf);
    for(long long i = 0; i < n; i++)
    {
        buk[buf[i] - 'a']++;
    }
    long long all = fact(n);
    long long odd = 0;
    long long num = 1;
    for(long long i = 0; i <= 'z' - 'a'; i++)
    {
        if(buk[i] & 1)
        {
            num = buk[i]--;
            odd++;
        }
    }
    if(odd > 1){ printf("%lld", all); }
    else
    {
        long long part = 1;
        for(long long i = 2; i <= n / 2; i++)
        {
            part = (i * part) % p;
        }
        long long tag = 1;
        for(long long i = 0; i <= 'z' - 'a'; i++)
        {
            if(buk[i] == 0){ continue; }
            for(long long j = buk[i], k = 1; k <= (buk[i] + 1) / 2; j--, k++)
            {
                part = (part * j) % p;
                tag = (tag * j) % p;
            }
        }
        if(odd == 1)
        {
            part = (num * part) % p;
        }
        long long ans = ((all - part) + p) % p;
        printf("%lld", ans);
    }
    return 0;
}
