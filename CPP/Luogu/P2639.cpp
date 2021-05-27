#include <stdio.h>
#include <algorithm>
using namespace std;
int f[100007];
int n, h;
int w[1007];
int main()
{
    scanf("%d%d", &h, &n);
    for(int i = 1; i <= n; i++)
    {
        scanf("%d", &w[i]);
    }
    for(int i = 1; i <= n; i++)
    {
        for(int j = h; j >= w[i]; j--)
        {
            f[j] = max(f[j], f[j - w[i]] + w[i]);
        }
    }
    printf("%d", f[h]);
    return 0;
}
