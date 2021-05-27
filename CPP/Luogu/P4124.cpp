#include <stdio.h>
#include <string.h>
using namespace std;
long long l, r;
int digit[12];
long long f[12][12][12][2][2][2];
long long dfs(int pos, int p, int pp, bool fr, bool et, bool thr, bool limit)
{
    if(et && fr)
    {
        return 0;
    }
    if(pos == -1)
    {
        return thr ? 1 : 0;
    }
    if(!limit && f[pos][p][pp][fr ? 1 : 0][et ? 1 : 0][thr ? 1 : 0] >= 0)
    {
        return f[pos][p][pp][fr ? 1 : 0][et ? 1 : 0][thr ? 1 : 0];
    }
    int up = limit ? digit[pos] : 9;
    long long sum = 0;
    for(int i = 0; i <= up; i++)
    {
        bool b = pp == p && p == i;
        sum += dfs(pos - 1, i, p, fr || i == 4, et || i == 8, thr || b, limit && i == digit[pos]);
    }
    if(!limit)
    {
        f[pos][p][pp][fr ? 1 : 0][et ? 1 : 0][thr ? 1 : 0] = sum;
    }
    return sum;
}
long long solve(long long x)
{
    if(x < 10000000000)
    {
        return 0;
    };
    int cnt = 0;
    while(x)
    {
        digit[cnt++] = x % 10;
        x /= 10;
    }
    long long res = 0;
    for(int i = 1; i <= digit[cnt - 1]; i++)
        res += dfs(cnt - 2, i, -1, i == 4, i == 8, false, i == digit[cnt - 1]);
    return res;
}
int main()
{
    memset(f, -128 / 2, sizeof(f));
    scanf("%lld%lld", &l, &r);
    printf("%lld", solve(r) - solve(l - 1));
    return 0;
}
