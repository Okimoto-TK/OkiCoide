#include <stdio.h>
#include <algorithm>
using namespace std;
int n, v;
int w[10007];
int p[10007];
int f[20007];
int main()
{
    scanf("%d%d", &n, &v);
    for(int i = 1; i <= n; i++)
    {
        scanf("%d%d", &w[i], &p[i]);
    }
    for(int i = 1; i <= n; i++)
    {
        for(int j = v; j >= w[i]; j--)
        {
            f[j] = max(f[j], f[j - w[i]] + p[i]);
        }
    }
    printf("%d", f[v]);
    return 0;
}
