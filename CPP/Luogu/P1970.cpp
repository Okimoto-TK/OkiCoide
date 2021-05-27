#include <cstdio>
#include <algorithm>
#define N 100007
int n;
int h[N];
int f[N][2];
int main()
{
    scanf("%d", &n);
    for(int i = 1; i <= n; i++) scanf("%d", &h[i]);
    f[1][1] = f[1][0] = 1;
    for(int i = 2; i <= n; i++)
    {
        if(h[i] > h[i - 1]) f[i][1] = f[i - 1][0] + 1;
        else f[i][1] = f[i - 1][1];
        if(h[i] < h[i - 1]) f[i][0] = f[i - 1][1] + 1;
        else f[i][0] = f[i - 1][0];
        //printf("%d\n", std::max(f[i][0], f[i][1]));
    }
    printf("%d", std::max(f[n][0], f[n][1]));
    return 0;
}
