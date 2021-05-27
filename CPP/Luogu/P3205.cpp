#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
int n;
int a[1007];
int f[1007][1007][2];
const int p = 19650827;
int main()
{
    scanf("%d", &n);
    for(int i = 1; i <= n; i++)
    {
        scanf("%d", &a[i]);
    }
    for(int i = 1; i <= n; i++)
    {
        f[i][i][0] = 1;
    }
    for(int k = 2; k <= n; k++)
    {
        for(int i = 1; i + k - 1 <= n; i++)
        {
            int j = i + k - 1;
            if(a[i] < a[i + 1])
            {
                f[i][j][0] += f[i + 1][j][0];
                f[i][j][0] %= p;
            }
            if(a[i] < a[j])
            {
                f[i][j][0] += f[i + 1][j][1];
                f[i][j][0] %= p;
            }
            if(a[j] > a[i])
            {
                f[i][j][1] += f[i][j - 1][0];
                f[i][j][1] %= p;
            }
            if(a[j] > a[j - 1])
            {
                f[i][j][1] += f[i][j - 1][1];
                f[i][j][1] %= p;
            }
        }
    }
    printf("%d", (f[1][n][0] + f[1][n][1]) % p);
    return 0;
}
