#include <stdio.h>
#include <string.h>
#define MOD 1000000007
using namespace std;
int d;
char buf[10007];
int digit[10007];
int f[10007][107];
int dfs(int pos, int sum, bool limit, bool zero)
{
    if(pos == -1)
    {
        return !zero && sum == 0;
    }
    if(!limit && !zero && f[pos][sum] >= 0)
    {
        return f[pos][sum];
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
int main()
{
    memset(f, -128 / 2, sizeof(f));
    scanf("%s", buf);
    scanf("%d", &d);
    int len = strlen(buf);
    for(int i = 0; i < len; i++)
    {
        digit[len - i - 1] = buf[i] - '0';
    }
    printf("%d\n", dfs(len - 1, 0, true, true));
    return 0;
}
