#include <stdio.h>
#include <string.h>
using namespace std;
int l, r;
int digit[33];
int f[33][33][33];
int dfs(int pos, int cnt0, int cnt1, bool limit, bool zero)
{
    if(pos == -1)
    {
        return !zero && cnt0 >= cnt1;
    }
    if(!limit && !zero && f[pos][cnt0][cnt1] >= 0)
    {
        return f[pos][cnt0][cnt1];
    }
    int up = limit ? digit[pos] : 1;
    int res = 0;
    for(int i = 0; i <= up; i++)
    {
        if(i == 0 && zero)
        {
            res += dfs(pos - 1, cnt0, cnt1, limit && i == digit[pos], true);
            continue;
        }
        res += dfs(pos - 1, cnt0 + (i == 0), cnt1 + (i == 1), limit && i == digit[pos], false);
    }
    if(!limit && !zero)
    {
        f[pos][cnt0][cnt1] = res;
    }
    return res;
}
int solve(int x)
{
    if(!x)
    {
        return 0;
    }
    int cnt = 0;
    while(x)
    {
        digit[cnt++] = x % 2;
        x /= 2;
    }
    return dfs(cnt - 1, 0, 0, true, true);
}
int main()
{
    memset(f, -128 / 2, sizeof(f));
    scanf("%d%d", &l, &r);
    printf("%d", solve(r) - solve(l - 1));
    return 0;
}
