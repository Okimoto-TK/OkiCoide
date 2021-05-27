#include <cstdio>
#include <algorithm>
#include <cstring>
#define N 1002
#define M 5007
int n;
int f[N][M << 1];
int a[N];
int b[N];
int main()
{
    scanf("%d", &n);
    memset(f, 0x3f, sizeof(f));
    f[0][M] = 0;
    for(int i = 1; i <= n; i++) scanf("%d%d", &a[i], &b[i]);
    for(int i = 1; i <= n; i++)
    {
        for(int j = M - 5 * (i); j <= M + 5 * (i); j++)
        {
            f[i][j] = std::min(f[i][j], std::min(f[i - 1][j - (a[i] - b[i])], f[i - 1][j + (a[i] - b[i])] + 1));
        }
    }
    int min = 0x3f3f3f3f;
    int ans = 0x3f3f3f3f;
    for(int j = M - 5 * n; j <= M + 5 * n; j++)
    {
        //printf("%d: %d\n", j, f[n][j]);
        if(f[n][j] < 0x3f3f3f3f && abs(j - M) < min)
        {
            min = abs(j - M);
            ans = f[n][j];
        }
        else if(f[n][j] < 0x3f3f3f3f && abs(j - M) == min)
        {
            ans = std::min(ans, f[n][j]);
        }
    }
    printf("%d", ans);
    return 0;
}
