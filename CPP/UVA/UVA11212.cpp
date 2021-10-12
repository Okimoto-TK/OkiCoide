#include <cstdio>
#include <cstring>
#include <algorithm>
int n;
int a[10];
inline int h()
{
    int cnt = 0;
    for(int i = 1; i <= n; i++)
    {
        if(a[i] == a[i - 1] + 1) cnt++;
    }
    return n - cnt;
}
bool Dfs(int limit, int x)
{
    if(h() == 0) return true;
    if(3 * x + h() > 3 * limit) return false;
    int re[10], b[10];
    memcpy(re, a, sizeof(re));
    for(int l = 1; l <= n; l++)
    {
        if(a[l] == a[l - 1] + 1) continue;
        for(int r = l; r <= n; r++)
        {
            for(int i = 1; i <= n - (r - l + 1); i++)
            {
                if(i < l) b[i] = re[i];
                else b[i] = re[i + (r - l + 1)];
            }
            for(int i = 1; i <= l; i++)
            {
                for(int j = 1; j <= n; j++)
                {
                    if(j < i) a[j] = b[j];
                    else if(i <= j && j <= i + r - l) a[j] = re[j - i + l];
                    else a[j] = b[j - (r - l + 1)];
                    if(Dfs(limit, x + 1)) return true;
                }
            }
        }
    }
    memcpy(a, re, sizeof(a));
    return false;
}
int main()
{
    int T = 1;
    for(scanf("%d", &n); n != 0; scanf("%d", &n))
    {
        for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
        bool solve = false;
        for(int limit = 0; limit < 5; limit++)
        {
            if(Dfs(limit, 0))
            {
                printf("Case %d: %d\n", T, limit);
                solve = true;
                break;
            }
        }
        if(!solve) printf("Case %d: %d\n", T, 5);
        T++;
    }
    return 0;
}
