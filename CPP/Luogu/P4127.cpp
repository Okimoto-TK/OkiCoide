#include <stdio.h>
#include <string.h>
using namespace std;
long long a, b;
int digit[20];
long long f[20][200][200];
long long dfs(long long pos, int sum, long long st, bool limit, int mod)
{
    if(pos == -1)
    {
        if(sum == 0)
        {
            return 0;
        }
        else
        {
            if(st == 0 && mod == sum)
            {
                return 1;
            }
            else
            {
                return 0;
            }
        }
    }
    if(!limit && f[pos][sum][st] >= 0)
    {
        return f[pos][sum][st];
    }
    int up = limit ? digit[pos] : 9;
    long long res = 0;
    for(int i = 0; i <= up; i++)
    {
        res += dfs(pos - 1, sum + i, (st * 10 + i) % mod, limit && i == digit[pos], mod);
    }
    if(!limit)
    {
        f[pos][sum][st] = res;
    }
    return res;
}
long long solve(long long x)
{
    if(x == 0)
    {
        return 0;
    }
    int cnt = 0;
    while(x)
    {
        digit[cnt++] = x % 10;
        x /= 10;
    }
    long long res = 0;
    for(int p = 1; p <= 9 * cnt; p++)
    {
        memset(f, -128 / 2, sizeof(f));
        for(int i = 0; i <= digit[cnt - 1]; i++)
        {
            res += dfs(cnt - 2, i, i % p, i == digit[cnt - 1], p);
        }
    }
    return res;
}
int main()
{
    scanf("%lld%lld", &a, &b);
    printf("%lld", solve(b) - solve(a - 1));
    return 0;
}
