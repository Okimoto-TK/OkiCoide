#include <stdio.h>
#include <string.h>
using namespace std;
long long a, b;
int digit[20];
long long f[20][10][10];
long long dfs(int pos, int p, int pp, bool limit, bool zero)
{
    if(pos == -1)
    {
        return 1;
    }
    if(!limit && !zero && p != -1 && pp != -1 && f[pos][p][pp] >= 0)
    {
        return f[pos][p][pp];
    }
    int up = limit ? digit[pos] : 9;
    long long sum = 0;
    for(int i = 0; i <= up; i++)
    {
        if(!zero && (i == p || i == pp))
        {
            continue;
        }
        sum += dfs(pos - 1, (i == 0 && zero) ? -1 : i, p, (limit && i == digit[pos]), zero && i == 0);
    }
    if(!limit && !zero && p != -1 && pp != -1)
    {
        f[pos][p][pp] = sum;
    }
    return sum;
}
long long solve(long long x)
{
    if(x == -1)
    {
        return 0;
    }
    if(x == 0)
    {
        return 1;
    }
    int cnt = 0;
    while(x)
    {
        digit[cnt++] = x % 10;
        x /= 10;
    }
    long long res = 0;
    for(int i = 0; i <= digit[cnt - 1]; i++)
    {
        res += dfs(cnt - 2, i == 0 ? -1 : i, -1, i == digit[cnt - 1], i == 0);
    }
    return res;
}
int main()
{
    memset(f, -1, sizeof(f));
    scanf("%lld%lld", &a, &b);
    printf("%lld", solve(b) - solve(a - 1));
    return 0;
}
