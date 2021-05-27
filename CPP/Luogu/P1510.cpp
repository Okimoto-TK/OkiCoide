#include <stdio.h>
#include <algorithm>
using namespace std;
int v, n, c;
int p[10007];
int w[10007];
int f[10007];
int main()
{
    scanf("%d%d%d", &v, &n, &c);
    for(int i = 1; i <= n; i++)
    {
        scanf("%d%d", &p[i], &w[i]);
    }
    for(int i = 1; i <= n; i++)
    {
        for(int j = c; j >= 0; j--)
        {
            if(j - w[i] >= 0)
            {
                f[j] = max(f[j], f[j - w[i]] + p[i]);
            }
        }
    }
    int ans = -1;
    for(int i = 0; i <= c; i++)
    {
        if(f[i] >= v)
        {
            ans = i;
            break;
        }
    }
    if(ans == -1)
    {
        printf("Impossible");
    }
    else
    {
        printf("%d", c - ans);
    }
}
