#include <stdio.h>
#include <algorithm>
using namespace std;
int n, h, d;
int a[5007][2007];
int f[5007][2007];
int m[5007];
int main()
{
    scanf("%d%d%d", &n, &h, &d);
    for(int i = 1; i <= n; i++)
    {
        scanf("%d", &a[i][0]);
        for(int j = 1; j <= a[i][0]; j++)
        {
            int k;
            scanf("%d", &k);
            a[i][k] += 1;
        }
    }
    for(int k = h; k >= 1; k--)
    {
        for(int i = 1; i <= n; i++)
        {
            f[k][i] = max(m[k + d], f[k + 1][i]) + a[i][k];
            m[k] = max(m[k], f[k][i]);
        }
    }
    printf("%d", m[1]);
    return 0;
}
