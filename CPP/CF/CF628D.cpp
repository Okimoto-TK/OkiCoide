#include <stdio.h>
#include <string.h>
using namespace std;
int m, d;
char l[2007];
char r[2007];
int digit[2007];
long long f[2007][2007][2];
const int mod = 1000000007;
long long dfs(int pos, int r, bool oe, bool limit, bool zero)
{
    if(pos == -1)
    {
        return !zero && r == 0;
    }
    if(!limit && !zero && f[pos][r][oe] >= 0)
    {
        return f[pos][r][oe];
    }
    int up = limit ? digit[pos] : 9;
    long long res = 0;
    for(int i = 0; i <= up; i++)
    {
        if(i == 0 && zero)
        {
            (res += dfs(pos - 1, r, oe, limit && i == digit[pos], true)) %= mod;
        }
        else
        {
            bool _oe = !oe;
            if(_oe)
            {
                if(i == d)
                {
                    continue;
                }
            }
            else
            {
                if(i != d)
                {
                    continue;
                }
            }
            (res += dfs(pos - 1, (r * 10 + i) % m, _oe, limit && i == digit[pos], false)) %= mod;
        }
    }
    if(!limit && !zero)
    {
        f[pos][r][oe] = res;
    }
    return res;
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
    if(l[0] == '0')
    {
        return 0;
    }
    int len = strlen(l);
    long long x = 0;
    for(int i = len - 1; i >= 0; i--)
    {
        digit[len - 1 - i] = l[i] - '0';
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
    res += dfs(len - 1, 0, false, true, true);
    return res;
}
long long solver()
{
    if(r[0] == '0')
    {
        return 0;
    }
    int len = strlen(r);
    long long x = 0;
    for(int i = len - 1; i >= 0; i--)
    {
        digit[len - 1 - i] = r[i] - '0';
        (x += digit[len - 1 - i] * fstPwr(10, len - 1 - i) % mod) %= mod;
    }
    long long res = 0;
    res += dfs(len - 1, 0, false, true, true);
    return res;
}
int main()
{
    memset(f, -128 / 2, sizeof(f));
    scanf("%d%d", &m, &d);
    scanf("%s%s", l, r);
    printf("%lld", (solver() - solvel() + mod) % mod);
    return 0;
}
