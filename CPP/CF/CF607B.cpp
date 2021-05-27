#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
int n;
int a[1007];
int f[1007][1007];
int main()
{
    memset(f, 0x3f, sizeof(f));
    scanf("%d", &n);
    for(int i = 1; i <= n; i++)
    {
        scanf("%d", &a[i]);
        f[i][i] = 1;
    }
    for(int len = 2; len <= n; len++)
    {
        for(int i = 1; i + len - 1 <= n; i++)
        {
            int j = i + len - 1;
            for(int k = i; k < j; k++)
            {
                f[i][j] = min(f[i][k] + f[k + 1][j], f[i][j]);
            }
            if(a[i] == a[j])
            {
                if(len == 2)
                {
                    f[i][j] = 1;
                }
                f[i][j] = min(f[i][j], f[i + 1][j - 1]);
            }
        }
    }
    printf("%d", f[1][n]);
    return 0;
}
