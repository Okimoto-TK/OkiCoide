#include <stdio.h>
#include <string.h>
#include <math.h>
#include <algorithm>
using namespace std;
long long X, A, B;
bool able[12];
int digit[12];
long long f[12][100007];
bool check(long long x)
{
    while(x)
    {
        if(!able[x % 10])
        {
            return false;
        }
        x /= 10;
    }
    return true;
}
long long fstPow(long long x, int k)
{
    long long r = 1;
    while(k)
    {
        if(k & 1)
        {
            (r *= x) %= X;
        }
        (x *= x) %= X;
        k >>= 1;
    }
    return r;
}
long long dfs(int pos, long long r, bool limit, bool zero)
{
    if(pos == -1)
    {
        return (r == 0 && !zero);
    }
    if(!limit && !zero && f[pos][r] >= 0)
    {
        return f[pos][r];
    }
    int up = limit ? digit[pos] : 9;
    long long sum = 0;
    for(int i = 0; i <= up; i++)
    {
        if(i == 0 && !able[0] && !zero)
        {
            continue;
        }
        if(i != 0 && !able[i])
        {
            continue;
        }
        sum += dfs(pos - 1, (r + fstPow(10, pos) * i % X) % X, limit && i == digit[pos], zero && i == 0);
    }
    if(!limit && !zero)
    {
        f[pos][r] = sum;
    }
    return sum;
}
long long solve(long long x)
{
    if(!x)
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
    for(int i = 0; i <= digit[cnt - 1]; i++)
    {
        if(i != 0 && !able[i])
        {
            continue;
        }
        res += dfs(cnt - 2, fstPow(10, cnt - 1) * i % X, i == digit[cnt - 1], i == 0);
    }
    return res;
}
int main()
{
    memset(f, -128 / 2, sizeof(f));
    scanf("%lld%lld%lld", &X, &A, &B);
    int v;
    while(scanf("%1d", &v) != EOF)
    {
        able[v] = true;
    }
    if(X > 100000)
    {
        long long ans = 0;
        for(int i = ceil(double(A) / double(X)); i * X <= B; i++)
        {
            if(check(i * X))
            {
                ans++;
            }
        }
        printf("%lld", ans);
        return 0;
    }
    printf("%lld", solve(B) - solve(A - 1));
    return 0;
}
