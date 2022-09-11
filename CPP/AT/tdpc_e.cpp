#include <stdio.h>
#include <string.h>
#define MOD 1000000007
using namespace std;
int d;
char str[10007];
int digit[10007];
int f[10007][107];
int dfs(int pos, int sum, bool limit, bool zero)
{
    if(pos == -1)
    {
        return sum == 0 && !zero;
    }
    if(!limit && !zero && f[pos][sum] >= 0)
    {
        return (f[pos][sum] + MOD) % MOD;
    }
    int up = limit ? digit[pos] : 9;
    int res = 0;
    for(int i = 0; i <= up; i++)
    {
        (res += dfs(pos - 1, (sum + i) % d, limit && i == digit[pos], zero && i == 0)) %= MOD;
    }
    if(!limit && !zero)
    {
        f[pos][sum] = res;
    }
    return res;
}
int solve()
{
    int cnt = strlen(str);
    return dfs(cnt - 1, 0, true, true);
}
int main()
{
    memset(f, -128 / 2, sizeof(f));
    scanf("%d", &d);
    scanf("%s", str);
    int len = strlen(str);
    for(int i = 0; i <= len - 1; i++)
    {
        digit[i] = str[len - i - 1] - '0';
    }
    printf("%d\n", solve());
    return 0;
}
