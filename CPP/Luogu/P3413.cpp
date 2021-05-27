#include <stdio.h>
#include <string.h>
using namespace std;
char buf[1007];
long long dp[1007][11][11];
int digit[1007];
const int mod = 1000000007;
long long dfs(int pos, int p, int pp, bool limit, bool zero)
{
    if(pos == -1)
    {
        return 1;
    }
    if(!limit && !zero && p != -1 && pp != -1 && dp[pos][p][pp] >= 0)
    {
        return dp[pos][p][pp];
    }
    int up = limit ? digit[pos] : 9;
    long long sum = 0;
    for(int i = 0; i <= up; i++)
    {
        if(i == p || i == pp)
        {
            continue;
        }
        if(!zero)
        {
            (sum += dfs(pos - 1, i, p, limit && i == digit[pos], false)) %= mod;
        }
        else
        {
            (sum += dfs(pos - 1, (i == 0) ? -1 : i, -1, limit && i == digit[pos], zero && (i == 0))) %= mod;
        }
    }
    if(!limit && !zero && p != -1 && pp != -1)
    {
        dp[pos][p][pp] = sum;
    }
    return sum;
}
long long fstPwr(long long x, int k)
{
    long long r = 1;
    while(k)
    {
        if(k & 1)
        {
            (r *= x) %= mod;
        }
        k >>= 1;
        (x *= x) %= mod;
    }
    return r;
}
long long solvel()
{
    if(buf[0] == '0')
    {
        return 0;
    }
    int len = strlen(buf);
    long long x = 0;
    for(int i = len - 1; i >= 0; i--)
    {
        digit[len - 1 - i] = buf[i] - '0';
        (x += digit[len - 1 - i] * fstPwr(10, len - 1 - i) % mod) %= mod;
    }
    for(int i = 0; i <= len - 1; i++)
    {
        if(digit[i] != 0)
        {
            digit[i] -= 1;
            break;
        }
        else
        {
            digit[i] = 9;
        }
    }
    if(digit[len - 1] == 0)
    {
        len--;
    }
    if(len == 0)
    {
        return 0;
    }
    (x -= 1 - mod) %= mod;
    long long res = 0;
    res += dfs(len - 1, -1, -1, true, true);
    return (x + 1 - res) % mod;
}
long long solver()
{
    if(buf[0] == '0')
    {
        return 0;
    }
    int len = strlen(buf);
    long long x = 0;
    for(int i = len - 1; i >= 0; i--)
    {
        digit[len - 1 - i] = buf[i] - '0';
        (x += digit[len - 1 - i] * fstPwr(10, len - 1 - i) % mod) %= mod;
    }
    long long res = 0;
    res += dfs(len - 1, -1, -1, true, true);
    return (x + 1 - res) % mod;
}
int main()
{
    memset(dp, -128 / 2, sizeof(dp));
    scanf("%s", buf);
    long long l = solvel();
    scanf("%s", buf);
    long long r = solver();
    printf("%lld", (r - l + mod) % mod);
    return 0;
}
