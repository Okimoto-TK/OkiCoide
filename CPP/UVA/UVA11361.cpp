#include <stdio.h>
#include <string.h>
using namespace std;
int T;
int digit[11];
int f[11][10001][101];
int dfs(int pos, int st, int sum, bool limit, int k, bool zero)
{
    if(pos == -1)
    {
        return !zero && st % k == 0 && sum % k == 0;
    }
    if(!limit && !zero && f[pos][st][sum] >= 0)
    {
        return f[pos][st][sum];
    }
    int up = limit ? digit[pos] : 9;
    int res = 0;
    for(int i = 0; i <= up; i++)
    {
        res += dfs(pos - 1, (st * 10 + i) % k, (sum + i) % k, limit && i == digit[pos], k, zero && i == 0);
    }
    if(!limit && !zero)
    {
        f[pos][st][sum] = res;
    }
    return res;
}
int solve(int x, int k)
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
    return dfs(cnt - 1, 0, 0, true, k, true);
}
int main()
{
    for(scanf("%d", &T); T; T--)
    {
        memset(f, -128 / 2, sizeof(f));
        int l, r, k;
        scanf("%d%d%d", &l, &r, &k);
        printf("%d\n", solve(r, k) - solve(l - 1, k));
    }
    return 0;
}
