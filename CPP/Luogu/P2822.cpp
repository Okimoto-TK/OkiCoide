#include <cstdio>
#include <algorithm>
#define N 2002
int t, k;
int map[N][N];
int sum[N][N];
int main()
{
    scanf("%d%d", &t, &k);
    for(int i = 0; i <= N - 2; i++)
    {
        for(int j = 0; j <= i; j++)
        {
            if(j == 0 || j == i) map[i][j] = 1;
            else (map[i][j] = map[i - 1][j] + map[i - 1][j - 1]) %= k;
            if(i == 0) sum[i][j] = 0;
            else
            {
                if(j == 0) sum[i][j] = 0;
                else sum[i][j] = sum[i][j - 1] + (map[i][j] == 0 ? 1 : 0);
            }
        }
    }
    for(; t != 0; t--)
    {
        int ans = 0;
        int n, m;
        scanf("%d%d", &n, &m);
        for(int i = 0; i <= n; i++) ans += sum[i][std::min(i, m)];
        printf("%d\n", ans);
    }
    return 0;
}
