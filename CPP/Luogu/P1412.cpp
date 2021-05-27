#include <stdio.h>
#include <algorithm>
using namespace std;
int n, k, c, w;
int a[100007];
bool b[100007];
double f[100007];
int main()
{
    scanf("%d%d%d%d", &n, &k, &c, &w);
    for(int i = 1; i <= n; i++)
    {
        int type;
        scanf("%d", &type);
        b[i] = (type == 1);
        scanf("%d", &a[i]);
    }
    for(int i = n; i >= 1; i--)
    {
        if(b[i])
        {
            f[i] = max(f[i + 1], f[i + 1] * (1.0 - 0.01 * k) + a[i] * w);
        }
        else
        {
            f[i] = max(f[i + 1], f[i + 1] * (1.0 + 0.01 * c) - a[i] * w);
        }
    }
    printf("%.2f", f[1]);
    return 0;
}
