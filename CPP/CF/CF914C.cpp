#include <stdio.h>
#include <string.h>
#define MOD 1000000007
using namespace std;
char buf[1007];
int digit[1007];
long long f[1007][1007];
int g[1007];
int k;
int count(int x)
{
    int res = 0;
    while(x)
    {
        x &= (x - 1);
        res++;
    }
    return res;
}
long long dfs(int pos, int cnt, bool limit, int low)
{
    if(pos == -1)
    {
        if(cnt == 0)
        {
            return 0;
        }
        if(cnt == 1 && low == 0)
        {
            if(k == 0)
            {
                return 1;
            }
            else
            {
                return 0;
            }
        }
        return g[cnt] + 1 == k;
    }
    if(!limit && f[pos][cnt] >= 0)
    {
        return f[pos][cnt];
    }
    int up = limit ? digit[pos] : 1;
    long long res = 0;
    for(int i = 0; i <= up; i++)
    {
        (res += dfs(pos - 1, cnt + i, limit && i == digit[pos], i == 1 ? pos : low)) %= MOD;
    }
    if(!limit)
    {
        f[pos][cnt] = res;
    }
    return res;
}
long long solve()
{
    int cnt = 0;
    int i = strlen(buf) - 1;
    while(i >= 0)
    {
        digit[cnt++] = buf[i--] - '0';
    }
    long long res = dfs(cnt - 1, 0, true, -1);
    return res;
}
int main()
{
    memset(f, -128 / 2, sizeof(f));
    scanf("%s", buf);
    scanf("%d", &k);
    g[1] = 0;
    for(int i = 2; i <= 1000; i++)
    {
        g[i] = g[count(i)] + 1;
    }
    printf("%lld", solve());
    return 0;
}
