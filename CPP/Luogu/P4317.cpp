#include <stdio.h>
#include <string.h>
#define MOD 10000007
using namespace std;
long long n;
long long f[64][64];
int digit[64];
long long dfs(int pos, int cnt1, bool limit)
{
    if(pos == -1)
    {
        return cnt1 == 0 ? 1 : cnt1;
    }
    if(!limit && f[pos][cnt1] >= 0)
    {
        return f[pos][cnt1];
    }
    int up = limit ? digit[pos] : 1;
    long long res = 1;
    for(int i = 0; i <= up; i++)
    {
        (res *= dfs(pos - 1, cnt1 + (i == 1), limit && i == digit[pos])) %= MOD;
    }
    if(!limit)
    {
        f[pos][cnt1] = res;
    }
    return res;
}
long long solve(long long x)
{
    int cnt = 0;
    while(x)
    {
        digit[cnt++] = x % 2;
        x /= 2;
    }
    return dfs(cnt - 1, 0, true);
}
int main()
{
    memset(f, -128 / 2, sizeof(f));
    scanf("%lld", &n);
    printf("%d", (int)solve(n));
    return 0;
}
