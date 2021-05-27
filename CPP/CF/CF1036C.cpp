#include <stdio.h>
#include <string.h>
using namespace std;
long long l, r;
int digit[20];
int f[20][4];
long long dfs(int pos, int cnt, bool limit)
{
    if(pos == -1)
    {
        return 1;
    }
    if(!limit && f[pos][cnt] >= 0)
    {
        return f[pos][cnt];
    }
    int up = limit ? digit[pos] : 9;
    long long res = 0;
    for(int i = 0; i <= up; i++)
    {
        if(i != 0 && cnt == 3)
        {
            break;
        }
        res += dfs(pos - 1, cnt + (i == 0 ? 0 : 1), limit && i == digit[pos]);
    }
    if(!limit)
    {
        f[pos][cnt] = res;
    }
    return res;
}
long long solve(long long x)
{
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
    long long res = dfs(cnt - 1, 0, true);
    return res;
}
int main()
{
    memset(f, -128 / 2, sizeof(f));
    int t;
    for(scanf("%d", &t); t; t--)
    {
        scanf("%lld%lld", &l, &r);
        printf("%lld\n", solve(r) - solve(l - 1));
    }
    return 0;
}
